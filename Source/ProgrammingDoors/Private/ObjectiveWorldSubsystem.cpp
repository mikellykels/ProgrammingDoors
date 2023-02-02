// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "../ProgrammingDoorsGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveHud.h"

void UObjectiveWorldSubsystem::Deinitialize()
{
	ObjectiveWidget = nullptr;
	ObjectivesCompleteWidget = nullptr;
}

void UObjectiveWorldSubsystem::CreateObjectiveWidgets() 
{
	if (ObjectiveWidget == nullptr)
	{
		AProgrammingDoorsGameModeBase* GameMode = Cast<AProgrammingDoorsGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			ObjectiveWidget = CreateWidget<UObjectiveHud>(PlayerController, GameMode->ObjectiveWidgetClass);
			ObjectivesCompleteWidget = CreateWidget<UUserWidget>(PlayerController, GameMode->ObjectivesCompleteWidgetClass);
		}
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		if (!ObjectiveWidget->IsInViewport())
		{
			ObjectiveWidget->AddToViewport();
		}
		ObjectiveWidget->UpdateObjectiveText(GetCompletedObjectiveCount(), Objectives.Num());
	}
}

void UObjectiveWorldSubsystem::RemoveObjectiveWidget() 
{
	if (ObjectiveWidget)
	{
		ObjectiveWidget->RemoveFromViewport();
	}
}

void UObjectiveWorldSubsystem::DisplayObjectivesCompleteWidget()
{
	if (ObjectivesCompleteWidget)
	{
		ObjectivesCompleteWidget->AddToViewport(1);
	}
}

void UObjectiveWorldSubsystem::RemoveObjectivesCompleteWidget()
{
	if (ObjectivesCompleteWidget)
	{
		ObjectivesCompleteWidget->RemoveFromViewport();
	}
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive)
	{
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed)
	{
		RetObjective += TEXT("completed!");
	}
	return RetObjective;
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize)
	{
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent)
{
	int32 numRemoved = ObjectiveComponent->OnStateChanged().RemoveAll(this);
	check(numRemoved);
	Objectives.Remove(ObjectiveComponent);
}

uint32 UObjectiveWorldSubsystem::GetCompletedObjectiveCount()
{
	uint32 ObjectivesCompleted = 0u;
	for (const UObjectiveComponent* OC : Objectives)
	{
		if (OC && OC->GetState() == EObjectiveState::OS_Completed)
		{
			++ObjectivesCompleted;
		}
	}
	return ObjectivesCompleted;
}

void UObjectiveWorldSubsystem::OnMapStart()
{
	AProgrammingDoorsGameModeBase* GameMode = Cast<AProgrammingDoorsGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		CreateObjectiveWidgets();

		GetWorld()->GetTimerManager().SetTimer(WidgetTimerHandle, this, &UObjectiveWorldSubsystem::AddWidget, 1.f, false, 15.0f);
	}
}

void UObjectiveWorldSubsystem::AddWidget()
{
	DisplayObjectiveWidget();
}

void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState)
{
	if (Objectives.Num() == 0 || !Objectives.Contains(ObjectiveComponent))
	{
		return;
	}

	if (!ObjectiveWidget || !ObjectivesCompleteWidget)
	{
		return;
	}

	if (ObjectiveWidget && ObjectivesCompleteWidget)
	{
		if (GetCompletedObjectiveCount() == Objectives.Num())
		{
			RemoveObjectiveWidget();
			DisplayObjectivesCompleteWidget();
		}
		else if (ObjectiveWidget)
		{
			DisplayObjectiveWidget();
		}
	}
}
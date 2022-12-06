// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProgrammingDoorsGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AProgrammingDoorsGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}

	if (ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(50.0f, 50.0f);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UPickupComponent::OnOverlapEnd);
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(TimerWidgetClass))
	{
		TimerWidget = CreateWidget<UTimerWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), TimerWidgetClass);
		GetWorld()->GetTimerManager().SetTimer(WidgetTimerHandle, this, &UPickupComponent::AddWidget, 1.f, false, 15.0f);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPickupComponent::Countdown, 1.f, true, 16.0f);
}

void UPickupComponent::Countdown()
{
	if (Seconds != 0)
	{
		Seconds = Seconds - 1;
	}
	else
	{
		if (Minutes == 0)
		{
			// restart level if timer finished
			UGameplayStatics::OpenLevel(GetWorld(), "MazeLevel");
		}
		else
		{
			Minutes = Minutes - 1;
			Seconds = 59;

		}
	}
	DisplayTimer();
}

void UPickupComponent::DisplayTimer()
{
	FNumberFormattingOptions Opts;
	Opts.SetMinimumIntegralDigits(2);
	TimerWidget->MinutesLabel->SetText(FText::AsNumber(GetMinutes(), &Opts));
	TimerWidget->SecondsLabel->SetText(FText::AsNumber(GetSeconds(), &Opts));
}

void UPickupComponent::AddTime()
{
	if (!Triggered)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("+ 10 Seconds!"));

		Seconds = Seconds + 10;
		if (Seconds > 59)
		{
			Minutes = Minutes + 1;
			Seconds = Seconds - 60;
		}
	}
}

void UPickupComponent::AddWidget()
{
	TimerWidget->AddToViewport(0);
}

void UPickupComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AddTime();
	Triggered = true;
	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);
}

void UPickupComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PickupState = EPickupState::PS_Active;
	Triggered = false;
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPickupComponent::Countdown, 1.f, true, 0.0);
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PickupState == EPickupState::PS_Active)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				OnPickup();
			}
		}
	}
}

void UPickupComponent::OnPickup()
{
	PickupState = EPickupState::PS_PickedUp;
	Triggered = true;
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, TEXT("Item picked up: + :10 seconds"));

	//UE_LOG(LogTemp, Error, TEXT("Active"));
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UPickupComponent::AddTime);
}

void UPickupComponent::Countdown()
{
	bool Active = GetWorld()->GetTimerManager().IsTimerActive(TimerHandle);
	if (Active)
	{
		//UE_LOG(LogTemp, Error, TEXT("Active"));
	}
	else if (!Active)
	{
		//UE_LOG(LogTemp, Error, TEXT("NOT Active"));
	}
	if (Seconds != 0)
	{
		Seconds = Seconds - 1;
		//UE_LOG(LogTemp, Warning, TEXT("Active Seconds: %d"), Seconds);
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
	//bool Active = GetWorld()->GetTimerManager().IsTimerActive(TimerHandle);

	//if (Active && Triggered) 
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Active"));
	//	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	//	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	//	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UPickupComponent::AddTime);
	//}
	//else if (!Active || !Triggered)
	//{
	//	if (PickupState == EPickupState::PS_PickedUp)
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("PICKED UP"));
	//	}

	//	if (Seconds != 0)
	//	{
	//		Seconds = Seconds - 1;
	//		UE_LOG(LogTemp, Warning, TEXT("Active Seconds: %d"), Seconds);
	//	}
	//	else
	//	{
	//		if (Minutes == 0)
	//		{
	//			// restart level if timer finished
	//			UGameplayStatics::OpenLevel(GetWorld(), "MazeLevel");
	//		}
	//		else
	//		{
	//			Minutes = Minutes - 1;
	//			Seconds = 59;

	//		}
	//	}
	//}
}

void UPickupComponent::AddTime()
{
	Triggered = false;
	Seconds = Seconds + 10;
}

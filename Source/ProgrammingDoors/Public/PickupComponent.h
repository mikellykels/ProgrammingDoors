// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "PickupComponent.generated.h"

class ATriggerBox;

UENUM()
enum class EPickupState
{
	PS_Inactive = 0 UMETA(DisplayName = "Inactive"),
	PS_Active = 1   UMETA(DisplayName = "Active"),
	PS_PickedUp = 2 UMETA(DisplayName = "Picked up")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGDOORS_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

	void OnPickup();

	UPROPERTY(BlueprintReadOnly)
	EPickupState PickupState;

	void Countdown();
	void AddTime();

	UPROPERTY(BlueprintReadOnly)
	int Minutes = 1;

	UPROPERTY(BlueprintReadOnly)
	int Seconds = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;

	UPROPERTY(BlueprintReadOnly)
	bool Triggered;

	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

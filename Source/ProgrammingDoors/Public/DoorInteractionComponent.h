// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

UENUM()
enum class EDoorState
{
	DS_Closed = 0   UMETA(DisplayName = "Closed"),
	DS_Closing = 1  UMETA(DisplayName = "Closing"),
	DS_Opening = 2  UMETA(DisplayName = "Opening"),
	DS_Open = 3     UMETA(DisplayName = "Open"),
	DS_Locked = 4   UMETA(DisplayName = "Locked"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGDOORS_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	static void OnDebugToggled(IConsoleVariable* var);
	void DebugDraw();

	void OnDoorOpen();
	void OnDoorClose();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	FRotator DesiredCloseRotation = FRotator::ZeroRotator;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator StartCloseRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;
	FRotator FinalCloseRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve CloseCurve;

	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

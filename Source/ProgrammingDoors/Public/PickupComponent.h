// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerWidget.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "PickupComponent.generated.h"

class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGDOORS_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

	void Countdown();
	void AddTime();
	void AddWidget();
	bool Triggered = false;

	int GetMinutes() const
	{
		return Minutes;
	}

	int GetSeconds() const
	{
		return Seconds;
	}

	void DisplayTimer();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UCapsuleComponent* GetTriggerCapsule() const
	{
		return TriggerCapsule;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule;

	UPROPERTY(BlueprintReadOnly)
	int Minutes = 2;

	UPROPERTY(BlueprintReadOnly)
	int Seconds = 0;

	FTimerHandle TimerHandle;
	FTimerHandle WidgetTimerHandle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UTimerWidget> TimerWidgetClass = nullptr;

private:
	UPROPERTY()
	UTimerWidget* TimerWidget = nullptr;
		
};

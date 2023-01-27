// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectivePickupItemComponent.generated.h"

class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGDOORS_API UObjectivePickupItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectivePickupItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UCapsuleComponent* GetTriggerCapsule() const
	{
		return TriggerCapsule;
	}

protected:
	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule;

private:
	UPROPERTY()
	bool Active;
};

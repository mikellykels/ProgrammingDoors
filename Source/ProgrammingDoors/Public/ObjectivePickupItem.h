// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectivePickupItem.generated.h"

class UObjectivePickupItemComponent;
class UObjectiveComponent;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class PROGRAMMINGDOORS_API AObjectivePickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectivePickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, NoClear)
	UObjectivePickupItemComponent* ObjectivePickupItemComponent;

	UPROPERTY(EditAnywhere, NoClear)
	UObjectiveComponent* ObjectiveComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* StaticMeshComponent;
};

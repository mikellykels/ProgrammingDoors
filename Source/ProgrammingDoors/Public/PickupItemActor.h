// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItemActor.generated.h"

class UPickupComponent;
class UStaticMeshComponent;

UCLASS()
class PROGRAMMINGDOORS_API APickupItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UPickupComponent* PickupComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Static Mesh")
	UStaticMeshComponent* StaticMeshComponent;
};

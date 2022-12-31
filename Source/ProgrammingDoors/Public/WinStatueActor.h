// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinStatueActor.generated.h"

class UStaticMeshComponent;
class UWinComponent;

UCLASS()
class PROGRAMMINGDOORS_API AWinStatueActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinStatueActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UWinComponent* WinComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* StaticMeshComponent;
};

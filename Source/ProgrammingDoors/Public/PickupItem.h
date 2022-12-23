// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PickupItem.generated.h"

class UPickupComponent;

/**
 * 
 */
UCLASS()
class PROGRAMMINGDOORS_API APickupItem : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	APickupItem();

protected:
	UPROPERTY(EditAnywhere, NoClear)
	UPickupComponent* PickupComponent;
};

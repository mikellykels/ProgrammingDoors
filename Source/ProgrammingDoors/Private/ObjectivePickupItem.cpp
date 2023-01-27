// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivePickupItem.h"
#include "Components/CapsuleComponent.h"
#include "ObjectivePickupItemComponent.h"
#include "ObjectiveComponent.h"

// Sets default values
AObjectivePickupItem::AObjectivePickupItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectiveComponent = CreateDefaultSubobject<UObjectiveComponent>(TEXT("ObjectiveComponent"));

	ObjectivePickupItemComponent = CreateDefaultSubobject<UObjectivePickupItemComponent>(TEXT("ObjectivePickupItemComponent"));
	if (ObjectivePickupItemComponent->GetTriggerCapsule())
	{
		RootComponent = ObjectivePickupItemComponent->GetTriggerCapsule();
	}

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectivePickupItemMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AObjectivePickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectivePickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

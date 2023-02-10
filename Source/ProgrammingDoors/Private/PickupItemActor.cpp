// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemActor.h"
#include "PickupComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APickupItemActor::APickupItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComp"));
	if (PickupComponent->GetTriggerCapsule())
	{
		RootComponent = PickupComponent->GetTriggerCapsule();
	}
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatueMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupItemActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

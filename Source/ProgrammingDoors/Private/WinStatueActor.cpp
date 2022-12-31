// Fill out your copyright notice in the Description page of Project Settings.


#include "WinStatueActor.h"
#include "WinComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AWinStatueActor::AWinStatueActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WinComponent = CreateDefaultSubobject<UWinComponent>(TEXT("WinComponent"));
	if (WinComponent->GetTriggerCapsule())
	{
		RootComponent = WinComponent->GetTriggerCapsule();
	}
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWinStatueActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinStatueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


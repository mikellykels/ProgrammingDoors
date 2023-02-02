// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivePickupItemComponent.h"
#include "Components/CapsuleComponent.h"
#include "ObjectiveComponent.h"

// Sets default values for this component's properties
UObjectivePickupItemComponent::UObjectivePickupItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Active = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(100.0f, 100.0f);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UObjectivePickupItemComponent::OnOverlapBegin);
}


// Called when the game starts
void UObjectivePickupItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UObjectivePickupItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectivePickupItemComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	TWeakObjectPtr<UObjectiveComponent> ObjectiveComponent;
	ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent == nullptr)
	{
		return;
	}
	ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	Active = false;
	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Item Collected"));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "WinComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWinComponent::UWinComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(125.0f, 125.0f);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UWinComponent::OnOverlapBegin);
}


// Called when the game starts
void UWinComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(WinWidgetClass))
	{
		WinWidget = CreateWidget<UWinWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WinWidgetClass);
		WinWidget->AddToViewport(0);
	}
	
}


// Called every frame
void UWinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWinComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DisplayWinWidget();
	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(RestartGameTimerHandle, this, &UWinComponent::OnWinTimerFinished, TimeRestartGameAfterWin, false);
}

void UWinComponent::OnWinTimerFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(), "WinMenuLevel");
}

void UWinComponent::DisplayWinWidget()
{
	WinWidget->WinLabel->SetText(FText::FromString("YOU WIN!!!"));
}

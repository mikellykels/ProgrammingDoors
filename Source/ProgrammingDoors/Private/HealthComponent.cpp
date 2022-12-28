// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(HealthWidgetClass))
	{
		HealthWidget = CreateWidget<UHealthWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), HealthWidgetClass);
		HealthWidget->AddToViewport(0);

		DisplayHealth();
	}
	
}

void UHealthComponent::DisplayHealth()
{
	HealthWidget->HealthBar->SetPercent(GetCurrentHealth() / GetMaxHealth());

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	HealthWidget->CurrentHealthLabel->SetText(FText::AsNumber(GetCurrentHealth(), &Opts));
	HealthWidget->MaxHealthLabel->SetText(FText::AsNumber(GetMaxHealth(), &Opts));
}

void UHealthComponent::TakeDamageEvent() 
{
	ChangedDamageEvent.Broadcast(this);
}



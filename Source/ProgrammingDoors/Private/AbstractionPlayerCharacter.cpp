// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractionPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AAbstractionPlayerCharacter::AAbstractionPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AAbstractionPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PC = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AAbstractionPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAbstractionPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAbstractionPlayerCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	UE_LOG(LogTemp, Warning, TEXT("Fell out"));
	HealthComponent->SetCurrentHealth(0.0f);
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	OnDeath(true);
}

float AAbstractionPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (HealthComponent && !HealthComponent->IsDead())
	{
		HealthComponent->TakeDamage(Damage);
		HealthComponent->TakeDamageEvent();
		PC->PlayerCameraManager->StartCameraShake(CamShake, 3.0f);
		OnDamage();
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return Damage;
}

void AAbstractionPlayerCharacter::OnDeath(bool IsFellOut)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("On Death"));
		PlayerController->DisableInput(PlayerController);
	}
	GetWorld()->GetTimerManager().SetTimer(RestartLevelTimerHandle, this, &AAbstractionPlayerCharacter::OnDeathTimerFinished, TimeRestartLevelAfterDeath, false);
}

void AAbstractionPlayerCharacter::OnDeathTimerFinished()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

const bool AAbstractionPlayerCharacter::IsAlive() const
{
	if (HealthComponent)
	{
		return !HealthComponent->IsDead();
	}
	return false;
}

const float AAbstractionPlayerCharacter::GetCurrentHealth() const
{
	if (HealthComponent)
	{
		return HealthComponent->GetCurrentHealth();
	}
	return 0.0f;
}
void AAbstractionPlayerCharacter::HandleDamage()
{
	OnDamage();
}

void AAbstractionPlayerCharacter::HandleItemCollected()
{
	ItemsCollected++;
	// Play Effects here.
	PC->PlayerCameraManager->StartCameraShake(CamShake, 1.0f);

	ItemCollected();
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthWidget.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGDOORS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	DECLARE_EVENT_OneParam(FHealthComponent, FOnDamageTaken, UHealthComponent*)
	FOnDamageTaken& OnDamageChanged()
	{
		return ChangedDamageEvent;
	}

	void DisplayHealth();
	void AddWidget();

	void TakeDamage(float Damage)
	{
		CurrentHealth -= Damage;
	}

	void TakeDamageEvent();


	bool IsDead()
	{
		return CurrentHealth <= FLT_EPSILON;
	}

	float GetCurrentHealth() const
	{
		return CurrentHealth;
	}

	float GetMaxHealth() const
	{
		return MaxHealth;
	}

	void SetCurrentHealth(float Health);

	FOnDamageTaken ChangedDamageEvent;

private:
	UPROPERTY()
	UHealthWidget* HealthWidget = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UHealthWidget> HealthWidgetClass = nullptr;

	FTimerHandle WidgetTimerHandle;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	float CurrentHealth = 0.0f;
};

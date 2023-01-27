// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.generated.h"

/**
 * 
 */

class UObjectiveComponent;
class UObjectiveHud;
class UUserWidget;

UCLASS()
class PROGRAMMINGDOORS_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void OnMapStart();

	uint32 GetCompletedObjectiveCount();

private:
	UObjectiveHud* ObjectiveWidget = nullptr;
	UUserWidget* ObjectivesCompleteWidget = nullptr;
	// add/remove them
	// sign up for callback onchanged
	TArray<UObjectiveComponent*> Objectives;

	float Score = 0.0f;

protected:
	virtual void Deinitialize() override;

	void CreateObjectiveWidgets();

	void DisplayObjectiveWidget();
	void RemoveObjectiveWidget();

	void DisplayObjectivesCompleteWidget();
	void RemoveObjectivesCompleteWidget();

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);
};

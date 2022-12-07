// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProgrammingDoorsGameModeBase.h"
#include "ObjectiveWorldSubsystem.h"

void AProgrammingDoorsGameModeBase::StartPlay()
{
	Super::StartPlay();

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}
}

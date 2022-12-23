// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "PickupComponent.h"

APickupItem::APickupItem()
{
	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
}

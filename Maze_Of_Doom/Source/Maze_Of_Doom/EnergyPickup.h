// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "EnergyPickup.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_OF_DOOM_API AEnergyPickup : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnergyPickup();

	/* Override the WasCollected function = used Implemenation because it's a Blueprent Native Event */
	void WasCollected_Implementation() override;

	/*Public way to access the battery's power level*/
	float GetPower();

protected:
	/* Sets the amount of power the battery gives to the character*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float Power;
};

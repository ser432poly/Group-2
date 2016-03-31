// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "EnergyPickup.h"

//Set default values
AEnergyPickup::AEnergyPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	//the base power level of the battery
	Power = 1.f;
}


void AEnergyPickup::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	// Destroy the battery
	Destroy();
}

// report the power level of the battery
float AEnergyPickup::GetPower()
{
	return Power;
}



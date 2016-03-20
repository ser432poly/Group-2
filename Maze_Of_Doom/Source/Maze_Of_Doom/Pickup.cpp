// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//All pickups start active
	isActive = true;

	//Create static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//Return isActive state
bool APickup::IsActive() 
{
	return isActive;
}

//Change isActive state
void APickup::SetActive(bool NewPickupState)
{
	isActive = NewPickupState;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class MAZE_OF_DOOM_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();
	ARoom(int roomType);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintPure, Category = "Room")
	void RotateRoom(int Rotates);

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
	int getDoor(int door);

	//Setter
	UFUNCTION(BlueprintCallable, Category = "Room")
	void setDoor(int door, int newValue);

	
private:
	//Index determines which wall, 0 = down, 1 = left, 2 = up, 3 = right
	//Value determines type of wall, 0 = wall, 1 = door, 2 = connected door, 3 = locked door, 4 = connected lock door
	int doors[4];

	//Used when spawning rooms to rotate room appropiately
	int direction = 0; //Every rooms first door is pointing down
};

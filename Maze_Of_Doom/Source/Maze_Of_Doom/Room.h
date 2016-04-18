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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		int32 getDoor(int32 door);

	//Setter
	UFUNCTION(BlueprintCallable, Category = "Room")
		void setDoor(int32 door, int32 newValue);

	//setter
	void setEndRoom();

	//setter
	void setPowerUp();

	//setter
	void setEnemy();

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		int32 getX();

	//Setter
	UFUNCTION(BlueprintCallable, Category = "Room")
		void setPos(int32 x, int32 y);

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		int32 getY();
	
	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		int32 getType();

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		int32 getRotation();

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		bool isEndRoom();

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		bool hasPowerUp();

	//Getter
	UFUNCTION(BlueprintPure, Category = "Room")
		bool hasEnemy();

	void determineRoom();


private:
	//Index determines which wall, 0 = down, 1 = left, 2 = up, 3 = right
	//Value determines type of wall, 0 = wall, 1 = door, 2 = connected door, 3 = locked door, 4 = connected lock door
	int32 doors[4];

	//Position of Room from spawn room
	int32 x;
	int32 y;

	//Type of room 3 nums for each room type
	//0-4 deadends
	//5-9 across
	//10-14 2door
	//15-19 3door
	//20-24 4door
	int32 type;

	//how much to rotate the room
	int32 rotation;

	//determine if the room should have a power up
	bool powerUp;

	//determine if the room has the end stairs
	bool endRoom;

	bool enemy;
};

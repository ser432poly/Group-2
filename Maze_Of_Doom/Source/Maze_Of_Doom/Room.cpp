// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "Room.h"


// Sets default values
ARoom::ARoom(){}
ARoom::ARoom(int32 roomType)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//PrimaryActorTick.bCanEverTick = true;	

	if (roomType = 0) //DeadEnd Room
	{
		doors[0] = 1;
		doors[1] = 0;
		doors[2] = 0;
		doors[3] = 0;
	}
	else if (roomType = 1) //Across Room
	{
		doors[0] = 1;
		doors[1] = 0;
		doors[2] = 1;
		doors[3] = 0;
	}
	else if (roomType = 2) //2 Door Room
	{
		doors[0] = 1;
		doors[1] = 0;
		doors[2] = 0;
		doors[3] = 1;
	}
	else if (roomType = 3)//3 Door Room
	{
		doors[0] = 1;
		doors[1] = 1;
		doors[2] = 0;
		doors[3] = 1;
	}
	else//4 Door Room
	{
		doors[0] = 1;
		doors[1] = 1;
		doors[2] = 1;
		doors[3] = 1;
	}

}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ARoom::getDoor(int32 door)
{
	return doors[door];
}

void ARoom::setDoor(int32 door, int32 newValue)

{
	doors[door] = newValue;
}

//Rotates the room 90 * rotates
void ARoom::RotateRoom(int32 rotates)
{
	for (int32 i = 0; i < rotates; i++)
	{
		int32 temp = doors[0];
		doors[0] = doors[1];
		doors[1] = doors[2];
		doors[2] = doors[3];
		doors[3] = temp;
	}
}

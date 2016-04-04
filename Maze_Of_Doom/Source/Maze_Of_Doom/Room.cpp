// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "Room.h"


// Sets default values
ARoom::ARoom()
{
	x = 0;
	y = 0;
	doors[0] = 0;
	doors[1] = 0;
	doors[2] = 0;
	doors[3] = 0;
}

void ARoom::setType(int32 roomType)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//PrimaryActorTick.bCanEverTick = true;	

	if (roomType == 0) //DeadEnd Room
	{
		doors[0] = 1;
		doors[1] = 0;
		doors[2] = 0;
		doors[3] = 0;
	}
	else if (roomType == 1) //Across Room
	{
		doors[0] = 1;
		doors[1] = 0;
		doors[2] = 1;
		doors[3] = 0;
	}
	else if (roomType == 2) //2 Door Room
	{
		doors[0] = 1;
		doors[1] = 0;
		doors[2] = 0;
		doors[3] = 1;
	}
	else if (roomType == 3)//3 Door Room
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

int32 ARoom::getDoor(int32 door)
{
	return doors[door];
}

void ARoom::setDoor(int32 door, int32 newValue)

{
	doors[door] = newValue;
}

int32 ARoom::getX()
{
	return x;
}

void ARoom::setPos(int32 newX, int32 newY)

{
	x = newX;
	y = newY;
}

int32 ARoom::getY()
{
	return y;
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

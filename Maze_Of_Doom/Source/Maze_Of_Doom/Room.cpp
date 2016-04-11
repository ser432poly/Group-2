// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "Room.h"


// Sets default values
ARoom::ARoom()
{
	x = 0;
	y = 0;
	doors[0] = 1;
	doors[1] = 1;
	doors[2] = 1;
	doors[3] = 1;
	type = 0;
}

int32 ARoom::getType()
{
	return type;

}

void ARoom::determineRoom()
{
	int32 count = 0;
	int32 rand = FMath::RandRange(0, 2);

	//count the doors
	for (int32 i = 0; i < 4; i++)
	{
		if (doors[i] != 0)
		{
			count += 1;
			rotation = i; //For deadend only and 4door
		}		
	}

	//determine type and rotation

	type = rand; //deadend
	if (count == 2) //2door
	{
		if (doors[0] == doors[3] && doors[0] != 0)
		{
			type += 6;
			rotation = 0;
		}
		else if (doors[1] == doors[0] && doors[1] != 0)
		{
			type += 6;
			rotation = 1;
		}
		else if (doors[2] == doors[1] && doors[2] != 0)
		{
			type += 6;
			rotation = 2;
		}
		else if (doors[3] == doors[2] && doors[3] != 0)
		{
			type += 6;
			rotation = 3;
		}
		//across
		else if  (doors[0] == doors[2] && doors[0] != 0)
		{
			type += 3;
			rotation = 0;
		}
		else
		{
			type += 3;
			rotation = 1;
		}
		
	}
	else if (count == 3) //3door
	{
		if (doors[0] == doors[3] && doors[2] == 0)
		{
			type += 9;
			rotation = 0;
		}
		else if (doors[1] == doors[0] && doors[3] == 0)
		{
			type += 9;
			rotation = 1;
		}
		else if (doors[2] == doors[1] && doors[0] == 0)
		{
			type += 9;
			rotation = 2;
		}
		else
		{
			type += 9;
			rotation = 3;
		}
	}
	else if (count == 4)//4door
	{
		type += 12;
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

int32 ARoom::getRotation()
{
	return rotation;
}

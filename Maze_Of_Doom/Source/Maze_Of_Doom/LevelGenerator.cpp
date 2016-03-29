// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "LevelGenerator.h"
#include <Room.h>
#include <stdlib.h>
#include <time.h>
#include <list>



// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();
	level = 1;

}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Generate the Level
void ALevelGenerator::CreateLevel()
{
	std::list<ARoom*> rooms; //Rooms that still need to connect all doors
	std::list<ARoom*> path; //Rooms that lead to the exit
	std::list<ARoom*> done; //Rooms that have all doors connected
	ARoom* currentRoom;
	int32 minPath = level % 5 + 5;
	int32 maxPath = level % 3 + 5;
	int32 roomLimit = 5 + level; //How many rooms to generate before all new rooms become deadends
	int32 chance;

	srand(time(NULL));
	int32 roomType = rand() % 5;

	//Create the spawn room
	ARoom* currentRoom = new ARoom(roomType);
	rooms.push_back(currentRoom);
	path.push_back(currentRoom);

	while (!rooms.empty)
	{
		for (int32 i = 0; i < 4; i++)
		{
			int32 door = currentRoom->getDoor(i);
			if (door == 1)
			{
				//Create a new Random Room
				chance = rand() % 100;
				chance = chance - level;
				if (chance > 50 || done.size >= roomLimit) //Early Levels more likely to create DeadEnds
				{
					roomType = 0;
				}
				else
				{
					roomType = rand() % 5;
				}
				ARoom* room = new ARoom(roomType);
			}
		}
	}
}

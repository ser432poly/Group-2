// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "LevelGenerator.h"
#include "Room.h"
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

void ALevelGenerator::addDone(ARoom r)
{
	done.push_back(r);
}

std::list<ARoom> ALevelGenerator::getDone()
{
	return done;
}

//Generate the Level
void ALevelGenerator::CreateLevel()
{
	std::list<ARoom*> rooms; //Rooms that still need to connect all doors
	ARoom* currentRoom; //Room that is being checked
	ARoom* room = nullptr; //Room that is being added to currentRoom
	int32 minPath = (level / 5) + 2;
	int32 maxPath = (level / 3) + 4;
	int32 roomLimit = 3 + level; //How many rooms to generate before all new rooms become deadends
	int32 chance;

	srand(time(NULL));
	int32 roomType = rand() % 5;

	//Create the spawn room and add it to the path
	currentRoom = ConstructObject<ARoom>(ARoom::StaticClass());
	currentRoom->setType(roomType);
	rooms.push_back(currentRoom);
	currentRoom->setPos(0, 0);

	//Keep adding rooms until all doors have rooms connected to them
	while (!rooms.empty())
	{
		//Rooms are made up of 4 walls
		for (int32 i = 0; i < 4; i++)
		{
			//Check if the current door is not already connected to a room
			if (currentRoom->getDoor(i) == 1)
			{
				//Check if the door isn't connected to a room
				for (std::list<ARoom*>::iterator it = rooms.begin(); it != rooms.end(); ++it)
				{
					//Get current room position
					int32 checkX = currentRoom->getX();
					int32 checkY = currentRoom->getY();
					int32 door;

					//Modify it based off of where current direction checking
					if (i == 0)
					{
						checkY = checkY - 1;
						door = 2;
					}
					else if (i == 1)
					{
						checkX = checkX - 1;
						door = 3;
					}
					else if (i == 2)
					{
						checkY = checkY + 1;
						door = 0;
					}
					else
					{
						checkX = checkX + 1;
						door = 1;
					}

					//Check if there is a room
					ARoom temp = *it;
					if (checkX == temp.getX() && checkY == temp.getY())
					{
						room = &temp;
						room->setDoor(door, 2);		
					}
				}

				for (std::list<ARoom*>::iterator it = done.begin(); it != done.end(); ++it)
				{
					//Get current room position
					int32 checkX = currentRoom->getX();
					int32 checkY = currentRoom->getY();
					int32 door;

					//Modify it based off of where current direction checking
					if (i == 0)
					{
						checkY = checkY - 1;
						door = 2;
					}
					else if (i == 1)
					{
						checkX = checkX - 1;
						door = 3;
					}
					else if (i == 2)
					{
						checkY = checkY + 1;
						door = 0;
					}
					else
					{
						checkX = checkX + 1;
						door = 1;
					}

					//Check if there is a room
					ARoom temp = *it;
					if (checkX == temp.getX() && checkY == temp.getY())
					{
						room = &temp;
						room->setDoor(door, 2);
					}
				}

				if (room == nullptr)
				{
					//Create a new Random Room
					chance = rand() % 100;
					chance = chance - level;
					//Only make dead ends once room limit is reached
					//Once room limit reach make all remaining doors dead ends
					if (((int32) done.size()) >= roomLimit)
					{
						roomType = 0;
					}
					else
					{
						roomType = rand() % 5;
					}

					//Create the room from the room type
					room = ConstructObject<ARoom>(ARoom::StaticClass());
					room->setType(roomType);

					//Always connect from door 0 so set door 0 to connected
					room->setDoor(0, 2);

					//Rotate room to connect doors correctly
					if (i == 0) //Room goes below current room
					{
						room->RotateRoom(2);
						room->setPos(currentRoom->getX(), currentRoom->getY() - 1);
					}
					else if (i == 1) //Room goes to left of current room
					{
						room->RotateRoom(3);
						room->setPos(currentRoom->getX() - 1, currentRoom->getY());
					}
					else if (i == 3) //Room goes to the right of current room
					{
						room->RotateRoom(3);
						room->setPos(currentRoom->getX() + 1, currentRoom->getY());
					}
					else //Room goes above current room
					{
						room->setPos(currentRoom->getX(), currentRoom->getY() + 1);
					}
					//Add the room to the rooms list
					rooms.push_back(room);
				}				

				//Set current door to be connected
				currentRoom->setDoor(i, 2);				
			}
			//clear the room
			room = nullptr;
		}
		//Checked all 4 walls

		//room is done
		rooms.pop_front();
		done.push_back(currentRoom);

		if (!rooms.empty())
		{
			*currentRoom = rooms.front();
		}
	}
}

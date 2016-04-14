// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze_Of_Doom.h"
#include "LevelGenerator.h"
#include "Room.h"
#include "Kismet/KismetMathLibrary.h"


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

}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelGenerator::addDone(ARoom* r)
{
	done.Add(r);
}

TArray<ARoom*> ALevelGenerator::getDone()
{
	return done;
}

//Generate the Level
void ALevelGenerator::CreateLevel(int32 level)
{
	TArray<ARoom*> rooms; //Rooms that still need to connect all doors
	ARoom* currentRoom; //Room that is being checked
	ARoom* room = 0; //Room that is being added to currentRoom
	int32 roomLimit = 2 + level; //How many rooms to generate before all new rooms become deadends
	int32 chance;
	//how many power ups to spawn
	int32 powerUps = level + 1;
	UWorld* const World = GetWorld();

	UE_LOG(LogClass, Log, TEXT("Level: %d"), level);

	//Create the spawn room and add it to the path
	currentRoom = World->SpawnActor<ARoom>();
	chance = FMath::RandRange(1, 5);
	//close some doors
	if (chance == 1) //4door
	{
	}
	else if (chance == 2) // 3door
	{
		currentRoom->setDoor(2, 0);
	}
	else if (chance == 3) // 2door
	{
		currentRoom->setDoor(1, 0);
		currentRoom->setDoor(2, 0);
	}
	else if (chance == 4) // across
	{
		currentRoom->setDoor(1, 0);
		currentRoom->setDoor(3, 0);
	}
	else //deadend
	{
		currentRoom->setDoor(1, 0);
		currentRoom->setDoor(2, 0);
		currentRoom->setDoor(3, 0);
	}

	rooms.Add(currentRoom);
	currentRoom->setPos(0, 0);

	//Keep adding rooms until all doors have rooms connected to them
	while (rooms.Num() > 0)
	{
		//Rooms are made up of 4 walls
		for (int32 i = 0; i < 4; i++)
		{
			//Check if the current door is not a wall
			if (currentRoom->getDoor(i) != 0)
			{
				//Check if the door isn't connected to a room
				for (auto it = rooms.CreateIterator(); it; ++it)
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
					ARoom* temp = *it;
					if (checkX == temp->getX() && checkY == temp->getY())
					{
						currentRoom->setDoor(i, temp->getDoor(door));
						room = temp;
					}
				}

				for (auto it = done.CreateIterator(); it; ++it)
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
					ARoom* temp = *it;
					if (checkX == temp->getX() && checkY == temp->getY())
					{
						currentRoom->setDoor(i, temp->getDoor(door));
						room = temp;
					}
				}

				if (!room)
				{
					//Create a new Random Room
					chance = FMath::RandRange(1, 100);
					chance = chance - level;

					//Create the room from the room type
					room = World->SpawnActor<ARoom>();

					//Only make dead ends once room limit is reached
					//Once room limit reach make all remaining doors dead ends
					if (((int32)done.Num()) >= roomLimit)
					{
						if (i == 0)
						{
							room->setDoor(0, 0);
							room->setDoor(1, 0);
							room->setDoor(2, 1);
							room->setDoor(3, 0);
						}
						else if (i == 1)
						{
							room->setDoor(0, 0);
							room->setDoor(1, 0);
							room->setDoor(2, 0);
							room->setDoor(3, 1);
						}
						else if (i == 2)
						{
							room->setDoor(0, 1);
							room->setDoor(1, 0);
							room->setDoor(2, 0);
							room->setDoor(3, 0);
						}
						else
						{
							room->setDoor(0, 0);
							room->setDoor(1, 1);
							room->setDoor(2, 0);
							room->setDoor(3, 0);
						}
						if (powerUps > 0)
						{
							room->setPowerUp();
							powerUps -= 1;
							UE_LOG(LogClass, Log, TEXT("Power Up1: %d"), currentRoom->getType());
						}
					}
					else //make a room that is not a dead end
					{
						if (i == 0)
						{
							for (int32 i = 0; i < 4; i++)
							{
								chance = FMath::RandRange(0, 1);
								room->setDoor(i, chance);
							}		
							//make sure right door is available
							room->setDoor(2, 1);
						}
						else if (i == 1)
						{
							for (int32 i = 0; i < 4; i++)
							{
								chance = FMath::RandRange(0, 1);
								room->setDoor(i, chance);
							}
							//make sure right door is available
							room->setDoor(3, 1);
						}
						else if (i == 2)
						{
							for (int32 i = 0; i < 4; i++)
							{
								chance = FMath::RandRange(0, 1);
								room->setDoor(i, chance);
							}
							//make sure right door is available
							room->setDoor(0, 1);
						}
						else
						{
							for (int32 i = 0; i < 4; i++)
							{
								chance = FMath::RandRange(0, 1);
								room->setDoor(i, chance);
							}
							//make sure right door is available
							room->setDoor(1, 1);
						}
					}

					//set position of room
					if (i == 0) //Room goes below current room
					{
						room->setPos(currentRoom->getX(), currentRoom->getY() - 1);
					}
					else if (i == 1) //Room goes to left of current room
					{
						room->setPos(currentRoom->getX() - 1, currentRoom->getY());
					}
					else if (i == 3) //Room goes to the right of current room
					{
						room->setPos(currentRoom->getX() + 1, currentRoom->getY());
					}
					else //Room goes above current room
					{
						room->setPos(currentRoom->getX(), currentRoom->getY() + 1);
					}
					//Add the room to the rooms list
					rooms.Add(room);
				}
			}
			//clear the room
			room = 0;
		}
		//Checked all 4 walls

		//room is done
		rooms.RemoveAt(0);
		currentRoom->determineRoom();
		addDone(currentRoom);
		UE_LOG(LogClass, Log, TEXT("Type: %d"), currentRoom->getType());
		UE_LOG(LogClass, Log, TEXT("Rot: %d"), currentRoom->getRotation());
		UE_LOG(LogClass, Log, TEXT("X: %d"), currentRoom->getX());
		UE_LOG(LogClass, Log, TEXT("Y: %d"), currentRoom->getY());

		if (rooms.Num() > 0)
		{
			currentRoom = rooms[0];
		}
		else
		{
			currentRoom->setEndRoom();
		}
	}
}

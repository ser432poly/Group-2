// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Maze_Of_Doom.h"
#include "Maze_Of_DoomGameMode.h"
#include "Maze_Of_DoomCharacter.h"

AMaze_Of_DoomGameMode::AMaze_Of_DoomGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

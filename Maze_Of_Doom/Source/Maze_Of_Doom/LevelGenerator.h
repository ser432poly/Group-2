// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MAZE_OF_DOOM_API ALevelGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Generate the level
	UFUNCTION(BlueprintCallable, Category = "Room")
	void CreateLevel();

	//getters
	UFUNCTION(BlueprintPure, Category = "Room")
	TArray<ARoom*> getDone();

	//setters
	void addDone(ARoom r);

private:
	int32 level = 1;
	TArray<ARoom*> done;
};

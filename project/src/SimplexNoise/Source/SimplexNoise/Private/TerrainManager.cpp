// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainManager.h"

// Sets default values
ATerrainManager::ATerrainManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATerrainManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrainManager::AdjustLandscapeSize()
{

}
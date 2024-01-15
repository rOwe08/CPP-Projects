// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainManager.h"
#include "SimplexNoiseConfig.h"
#include "Landscape.h"
#include "EngineUtils.h"

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

    AdjustLandscapeSize();
}

// Called every frame
void ATerrainManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrainManager::AdjustLandscapeSize()
{
    ALandscape* Landscape = FindLandscape();
    if (Landscape)
    {
        FVector NewScale = FVector(
            SimplexNoiseConfig::Scale,
            SimplexNoiseConfig::Scale,
            SimplexNoiseConfig::Scale
        );

        Landscape->SetActorScale3D(NewScale);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Landscape scaled to: %s"), *NewScale.ToString()));
        }
    }
}

ALandscape* ATerrainManager::FindLandscape()
{
    for (TActorIterator<ALandscape> It(GetWorld()); It; ++It)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Landscape found!"));
        }
        return *It;
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Landscape found."));
    }
    return nullptr;
}



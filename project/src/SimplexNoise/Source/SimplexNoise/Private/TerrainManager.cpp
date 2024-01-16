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

    SimplexNoiseGenerateLandscape();
}

// Called every frame
void ATerrainManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

//TArray<float> ATerrainManager::GenerateNoiseMap(int MapWidth, int MapHeight)
//{
//    // TODO: Simplex Noise generation
//}

void ATerrainManager::ApplyNoiseToLandscape(ALandscape* Landscape, const TArray<float>& NoiseMap)
{
    // TODO
}

void ATerrainManager::SimplexNoiseGenerateLandscape()
{
    ALandscape* Landscape = FindLandscape();

    if (!Landscape)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Landscape found. Cannot generate terrain."));
        }
        return;
    }

    //TArray<float> NoiseMap = GenerateNoiseMap(NoiseMapWidth, NoiseMapHeight);

    //ApplyNoiseToLandscape(Landscape, NoiseMap);
}




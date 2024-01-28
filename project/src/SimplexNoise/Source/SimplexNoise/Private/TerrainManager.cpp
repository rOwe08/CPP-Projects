// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainManager.h"
#include "SimplexNoiseConfig.h"
#include "SimplexNoiseHelper.h"
#include "ProceduralMeshComponent.h"
#include "EngineUtils.h"


// Sets default values
ATerrainManager::ATerrainManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
    ProceduralMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ATerrainManager::BeginPlay()
{
    Super::BeginPlay();

    ApplyConfigToLandscape();
    SimplexNoiseGenerateLandscape();
}

// Called every frame
void ATerrainManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ATerrainManager::ApplyConfigToLandscape()
{

}

void ATerrainManager::ApplyNoiseToLandscape(const TArray<float>& NoiseMap)
{

}


void ATerrainManager::SimplexNoiseGenerateLandscape()
{
    ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}
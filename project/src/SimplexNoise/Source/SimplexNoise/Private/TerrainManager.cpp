﻿// Fill out your copyright notice in the Description page of Project Settings.

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

    CreateVertices();
    CreateTriangles();
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

void ATerrainManager::CreateVertices()
{
    float Scale = 100.0f;

    for (int X = 0; X <= XSize; ++X) 
    {
        for (int Y = 0; Y <= YSize; ++Y) 
        {
            Vertices.Add(FVector( X * Scale, Y * Scale, 0));

            DrawDebugSphere(GetWorld(), FVector(X * Scale, Y * Scale, 0), 25.0f, 16, FColor::Red, true, -1.0f, 0U, 0.0f);
        }
    }
}

void ATerrainManager::CreateTriangles()
{
    int Vertex = 0;

    for (int i = 0; i < XSize; ++i) 
    {
        for (int j = 0; j < YSize; ++j)
        {
            Triangles.Add(Vertex);
            Triangles.Add(Vertex + 1);
            Triangles.Add(YSize + Vertex + 1);

            Triangles.Add(Vertex + 1);
            Triangles.Add(Vertex + YSize + 2);
            Triangles.Add(Vertex + YSize + 1);

            ++Vertex;
        }
        ++Vertex;
    }
}

void ATerrainManager::ApplyNoiseToLandscape(const TArray<float>& NoiseMap)
{

}


void ATerrainManager::SimplexNoiseGenerateLandscape()
{
    ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainManager.h"
#include "SimplexNoiseConfig.h"
#include "SimplexNoiseHelper.h"
#include "Landscape.h"
#include "LandscapeEdit.h"
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

void ATerrainManager::ApplyNoiseToLandscape(ALandscape* Landscape, const TArray<float>& NoiseMap)
{
    if (!Landscape) return;

    FLandscapeEditDataInterface LandscapeEditData(Landscape->GetLandscapeInfo());
    TArray<ULandscapeComponent*> LandscapeComponents;
    Landscape->GetComponents(LandscapeComponents);

    for (ULandscapeComponent* Component : LandscapeComponents)
    {
        FIntPoint ComponentOrigin = Component->GetSectionBase();
        int32 ComponentSize = Component->ComponentSizeQuads + 1;

        TArray<uint16> HeightData;
        HeightData.SetNumUninitialized(ComponentSize * ComponentSize);

        for (int32 Y = 0; Y < ComponentSize; ++Y)
        {
            for (int32 X = 0; X < ComponentSize; ++X)
            {
                int32 NoiseMapIndex = (ComponentOrigin.Y + Y) * ComponentSize + (ComponentOrigin.X + X);
                float NoiseValue = NoiseMap[NoiseMapIndex];
                uint16 Height = FMath::Clamp<uint16>(FMath::RoundToInt(NoiseValue * 65535.0f), 0, 65535);

                UE_LOG(LogTemp, Warning, TEXT("Noise Value at (%d): %f"), Y * ComponentSize + X, Height);
                    
                HeightData[Y * ComponentSize + X] = Height;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("THE END"));

        LandscapeEditData.SetHeightData(
            ComponentOrigin.X, ComponentOrigin.Y,
            ComponentOrigin.X + ComponentSize - 1, ComponentOrigin.Y + ComponentSize - 1,
            HeightData.GetData(),
            0, // InStride
            true, // InCalcNormals
            nullptr, // InNormalData
            nullptr, // InHeightAlphaBlendData
            nullptr, // InHeightRaiseLowerData
            false, // InCreateComponents
            nullptr, // InHeightmap
            nullptr, // InXYOffsetmapTexture
            true, // InUpdateBounds
            true, // InUpdateCollision
            false // InGenerateMips
        );
    }

    Landscape->MarkPackageDirty();
    Landscape->PostEditChange();
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

    TArray<float> NoiseMap = SimplexNoiseHelper::GenerateNoiseMap(SimplexNoiseConfig());
    ApplyNoiseToLandscape(Landscape, NoiseMap);
}
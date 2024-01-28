// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplexNoiseHelper.h"

//TArray<FVector> SimplexNoiseHelper::Vertices;
//TArray<int32> SimplexNoiseHelper::Triangles;

float SimplexNoiseHelper::GenerateNormalizedNoiseValue(float x, float y)
{
    float rawNoise = FMath::Sin(x * 0.1f) * FMath::Cos(y * 0.1f);
    return (rawNoise + 1.0f) / 2.0f;
}

TArray<float> SimplexNoiseHelper::GenerateNoiseMap(const SimplexNoiseConfig& Config)
{
    TArray<float> NoiseMap;
    NoiseMap.Init(0.0f, Config.MapWidth * Config.MapHeight);

    for (int y = 0; y < Config.MapHeight; y++)
    {
        for (int x = 0; x < Config.MapWidth; x++)
        {
            float noiseValue = GenerateNormalizedNoiseValue(x * Config.Scale + Config.Offset.X, y * Config.Scale + Config.Offset.Y);

            NoiseMap[y * Config.MapWidth + x] = noiseValue;
        }
    }

    for (int y = 0; y < Config.MapHeight; y++)
    {
        for (int x = 0; x < Config.MapWidth; x++)
        {
            float noiseValue = NoiseMap[y * Config.MapWidth + x];
            UE_LOG(LogTemp, Warning, TEXT("Noise Value at (%d, %d): %f"), x, y, noiseValue);
        }
    }

    return NoiseMap;
}
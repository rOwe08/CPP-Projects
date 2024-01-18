// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplexNoiseHelper.h"

float SimplexNoiseHelper::Generate(float x, float y)
{
    return 0;
}

TArray<float> SimplexNoiseHelper::GenerateNoiseMap(int Width, int Height, const SimplexNoiseConfig& Config)
{
    TArray<float> NoiseMap;
    NoiseMap.Init(0.0f, Width * Height);

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            float noiseValue = Generate(x * Config.Scale, y * Config.Scale);
            NoiseMap[y * Width + x] = noiseValue;
        }
    }

    return NoiseMap;
}

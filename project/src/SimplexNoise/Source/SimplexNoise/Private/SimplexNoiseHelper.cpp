// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplexNoiseHelper.h"

//TArray<FVector> SimplexNoiseHelper::Vertices;
//TArray<int32> SimplexNoiseHelper::Triangles;

float SimplexNoiseHelper::GenerateNormalizedNoiseValue(float x, float y)
{
    float rawNoise = FMath::Sin(x * 0.1f) * FMath::Cos(y * 0.1f);
    return (rawNoise + 1.0f) / 2.0f;
}

void SimplexNoiseHelper::GenerateNoiseMap(const SimplexNoiseConfig& Config)
{
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplexNoiseConfig.h"

class SimplexNoiseHelper
{
public:
    static float Generate(float x, float y);
    static TArray<float> GenerateNoiseMap(int Width, int Height, const SimplexNoiseConfig& Config);
private:
    static float SimplexNoise(float x, float y);
};

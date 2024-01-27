// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplexNoiseConfig.h"

class SimplexNoiseHelper
{
public:
    static float GenerateNormalizedNoiseValue(float x, float y);
    static TArray<float> GenerateNoiseMap(const SimplexNoiseConfig& Config);
private:
    static float SimplexNoise(float x, float y);
};

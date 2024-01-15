// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SIMPLEXNOISE_API SimplexNoiseConfig
{
public:
	SimplexNoiseConfig();
	~SimplexNoiseConfig();

public:
    static float Scale;
    static int Octaves;
    static float Persistence;
    static float Lacunarity;
    static FVector2D Offset;
    static int Seed; 

    static void SetNoiseParameters(float NewScale, int NewOctaves, float NewPersistence, float NewLacunarity, FVector2D NewOffset, int NewSeed)
    {
        Scale = NewScale;
        Octaves = NewOctaves;
        Persistence = NewPersistence;
        Lacunarity = NewLacunarity;
        Offset = NewOffset;
        Seed = NewSeed;
    }
};

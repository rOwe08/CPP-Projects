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
    static int XSize;
    static int YSize;

    static float Scale;
    static float UVScale;
    static int Octaves;
    static float Persistence;
    static float Lacunarity;
    static int Seed;
    static FVector2D Offset;
    //const std::array<FVector2D, 8> Gradients;

    //static void SetNoiseParameters(float NewScale, int NewOctaves, float NewPersistence, float NewLacunarity, FVector2D NewOffset, int NewSeed)
    //{
    //    Scale = NewScale;
    //    Octaves = NewOctaves;
    //    Persistence = NewPersistence;
    //    Lacunarity = NewLacunarity;
    //    Offset = NewOffset;
    //    Seed = NewSeed;
    //}
};

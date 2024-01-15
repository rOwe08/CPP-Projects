// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplexNoiseConfig.h"

SimplexNoiseConfig::SimplexNoiseConfig()
{
}

SimplexNoiseConfig::~SimplexNoiseConfig()
{
}

//Just random values for now
float SimplexNoiseConfig::Scale = 1.0f;
int SimplexNoiseConfig::Octaves = 1;
float SimplexNoiseConfig::Persistence = 0.5f;
float SimplexNoiseConfig::Lacunarity = 2.0f;
FVector2D SimplexNoiseConfig::Offset = FVector2D(0.0f, 0.0f);
int SimplexNoiseConfig::Seed = 1337;  
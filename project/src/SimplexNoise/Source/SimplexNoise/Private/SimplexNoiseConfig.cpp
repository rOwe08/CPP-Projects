// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplexNoiseConfig.h"

SimplexNoiseConfig::SimplexNoiseConfig()
{
}

SimplexNoiseConfig::~SimplexNoiseConfig()
{
}

//Just random values for now
int SimplexNoiseConfig::XSize = 500;
int SimplexNoiseConfig::YSize = 500;

float SimplexNoiseConfig::Scale = 300.0f;
float SimplexNoiseConfig::UVScale = 10.0f;

int SimplexNoiseConfig::Octaves = 6;
float SimplexNoiseConfig::Persistence = 0.5f;
float SimplexNoiseConfig::Lacunarity = 2.0f;
int SimplexNoiseConfig::Seed = 1337;
FVector2D SimplexNoiseConfig::Offset = FVector2D(0.0f, 0.0f);

//const std::array<FVector2D, 8> Gradients = {
//    FVector2D(1, 0), FVector2D(-1, 0), FVector2D(0, 1), FVector2D(0, -1),
//    FVector2D(1, 1).GetSafeNormal(), FVector2D(-1, 1).GetSafeNormal(),
//    FVector2D(1, -1).GetSafeNormal(), FVector2D(-1, -1).GetSafeNormal()
//};
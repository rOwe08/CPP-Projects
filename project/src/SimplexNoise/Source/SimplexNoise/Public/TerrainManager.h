// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Landscape.h"
#include "TerrainManager.generated.h"

UCLASS()
class SIMPLEXNOISE_API ATerrainManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ALandscape* FindLandscape();
	TArray<float> GenerateNoiseMap(int MapWidth, int MapHeight);
	void ApplyNoiseToLandscape(ALandscape* Landscape, const TArray<float>& NoiseMap);
	void SimplexNoiseGenerateLandscape();
};
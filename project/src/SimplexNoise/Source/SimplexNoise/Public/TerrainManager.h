// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
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

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere)
	TArray<int32> Triangles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyConfigToLandscape();
	void ApplyNoiseToLandscape(const TArray<float>& NoiseMap);
	void SimplexNoiseGenerateLandscape();
private:
	UProceduralMeshComponent* ProceduralMesh;

};
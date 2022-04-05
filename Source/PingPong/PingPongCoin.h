// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongCoin.generated.h"

UCLASS()
class PINGPONG_API APingPongCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APingPongCoin();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* BodyCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* BodyMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

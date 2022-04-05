// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongGate.generated.h"


UCLASS()
class PINGPONG_API APingPongGate : public AActor
{
	GENERATED_BODY()

public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class APingPongPlayerController* Player;


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BodyCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;
	
public:	
	// Sets default values for this actor's properties
	APingPongGate();

	DECLARE_EVENT_TwoParams(APingPongGate, FOnHit, APingPongPlayerController*, float)
	FOnHit OnHit;

	UFUNCTION()
	void BroadcastToGameMode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

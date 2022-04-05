// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PingPongGameMode.generated.h"


class APingPongGate;
class APingPongPlayerStart;
class APingPongPlayerController;

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	APingPongPlayerController* Player1 = NULL;

	UPROPERTY()
	APingPongPlayerController* Player2 = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APingPongPlayerStart* Player1Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APingPongPlayerStart* Player2Start;

	UFUNCTION(BlueprintCallable)
	void AddScore(APingPongPlayerController* Player, float Score);

public:

	APingPongGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Player1Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Player2Score = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FVector CenterPoint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APingPongCoin> CoinClass;

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	void SpawnCoin();

};

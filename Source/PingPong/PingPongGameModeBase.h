// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"

class APingPongGate;
class APingPongPlayerStart;
class APingPongPlayerController;

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
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

	APingPongGameModeBase();
	
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

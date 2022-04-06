// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"

class APingPongGate;
class APingPongPlatform;
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

	UPROPERTY(BlueprintReadWrite)
	APingPongPlayerController* Player1 = NULL;

	UPROPERTY(BlueprintReadWrite)
	APingPongPlayerController* Player2 = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APingPongPlayerStart* Player1Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APingPongPlayerStart* Player2Start;

	UFUNCTION(BlueprintCallable)
	void AddScore(FString Player, float Score);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreChanged, float, Player1Score, float, Player2Score);
	UPROPERTY(BlueprintAssignable)
	FScoreChanged OnScoreChanged;


public:

	APingPongGameModeBase();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FString Player1Name;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FString Player2Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APingPongPlatform* Player1Plat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APingPongPlatform* Player2Plat;

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

	virtual void Tick(float DeltaTime) override;
};

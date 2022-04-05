// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "PingPongGate.h"
#include "PingPongPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ping Pong Gate")
	APingPongGate* PingPongGate;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Components/Widget.h>
#include "PingPongBall.h"
#include "PingPongPlayerController.generated.h"

class APingPongPlatform;

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	FTransform StartTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<APingPongPlatform> PlatformClass;



public:


	APingPongPlayerController();

	UPROPERTY()
	APingPongPlatform* Platform;

	UPROPERTY()
	APingPongBall* Ball;

	UFUNCTION()
	void SetStartTransform(FTransform NewStartTransform);

	UFUNCTION(Server, Reliable, WithValidation)
	void Initialize();

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnPlatform(TSubclassOf<APingPongPlatform> NewPlatformClass);

	virtual void SetupInputComponent() override;

protected:
	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void RotateRight(float AxisValue);

	UFUNCTION()
	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlatformMoveRight(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlatformRotateRight(float AxisValue);

	virtual void BeginPlay() override;
};

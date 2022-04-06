// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongBall.generated.h"

UCLASS()
class PINGPONG_API APingPongBall : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class USphereComponent* BodyCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball Params")
	float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball Params")
	class UParticleSystem* HitEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString BouncedPlayer;
	
public:	
	// Sets default values for this actor's properties
	APingPongBall();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Move(float DeltaTime);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StartMove();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopMove();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multicast_ChangeColor(APingPongPlatform* Platform);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_HitEffect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartMove();

	UFUNCTION(BlueprintCallable)
	void StopMove();

	UFUNCTION(BlueprintCallable)
	void ChangeColor(APingPongPlatform* Platform);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Score = 1;

	UPROPERTY(Replicated)
	bool IsMoving = true;
};

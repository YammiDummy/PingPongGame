// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongBall.h"

#include <DrawDebugHelpers.h>
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Net/UnrealNetwork.h>
#include "PingPongGate.h"

// Sets default values
APingPongBall::APingPongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Ball Collision"));
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);

	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void APingPongBall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APingPongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetNetMode() != ENetMode::NM_Client)
	{
		Server_Move(DeltaTime);
	}

}

void APingPongBall::StartMove()
{
	Server_StartMove();
}

void APingPongBall::StopMove()
{
	Server_StopMove();
}

void APingPongBall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APingPongBall, IsMoving);
}

bool APingPongBall::Server_Move_Validate(float DeltaTime)
{
	return true;
}

void APingPongBall::Server_Move_Implementation(float DeltaTime)
{
	FVector ForwardVector = GetActorForwardVector();
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + ForwardVector * MoveSpeed * DeltaTime;

	FHitResult HitResult;
	if (!SetActorLocation(NewLocation, true, &HitResult) && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball %s Collided with %s"), *GetName(), *HitResult.GetActor()->GetName());

		FVector MoveVector = ForwardVector.MirrorByVector(HitResult.ImpactNormal);

		FVector ResetPosition = CurrentLocation - ForwardVector.MirrorByVector(HitResult.ImpactNormal);
		DrawDebugDirectionalArrow(GetWorld(), CurrentLocation, CurrentLocation + ForwardVector, 30, FColor::Yellow, true, 3.f, 0, 3);

		FVector ImpactCorrection = HitResult.ImpactPoint + HitResult.ImpactNormal * 300;
		DrawDebugDirectionalArrow(GetWorld(), HitResult.ImpactPoint, ImpactCorrection, 30, FColor::Blue, true, 3, 0, 3);

		FVector NewTargetMove = ResetPosition + MoveVector * 300;
		NewTargetMove.Z = CurrentLocation.Z;
		DrawDebugDirectionalArrow(GetWorld(), ResetPosition, ResetPosition + MoveVector * 300, 30, FColor::Green, true, 3.f, 0, 3);

		SetActorLocation(ResetPosition);
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, NewTargetMove);
		NewRotation.Pitch = CurrentRotation.Pitch;
		SetActorRotation(NewRotation);

		Score++;
		MoveSpeed += 30;

		Multicast_HitEffect();
	}
}

bool APingPongBall::Server_StartMove_Validate()
{
	return true;
}

void APingPongBall::Server_StartMove_Implementation()
{
	IsMoving = true;
}

bool APingPongBall::Server_StopMove_Validate()
{
	return true;
}

void APingPongBall::Server_StopMove_Implementation()
{
	IsMoving = false;
}

void APingPongBall::Multicast_HitEffect_Implementation()
{
	UWorld* World = GetWorld();
	if (World && HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation());
	}
}
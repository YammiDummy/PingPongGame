// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongCoin.h"
#include <Components/BoxComponent.h>

// Sets default values
APingPongCoin::APingPongCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Coin Collision"));
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin MeshS"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);

	SetReplicates(true);

}

// Called when the game starts or when spawned
void APingPongCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APingPongCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorRotation(GetActorRotation() + FRotator(0, 1, 0));
}


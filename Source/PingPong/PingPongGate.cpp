// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGate.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PingPongBall.h"

// Sets default values
APingPongGate::APingPongGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate Collision"));
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gate Mesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);

	SetReplicates(true);

	BodyCollision->OnComponentBeginOverlap.AddDynamic(this, &APingPongGate::BroadcastToGameMode);
}

void APingPongGate::BroadcastToGameMode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APingPongBall* Ball = Cast<APingPongBall>(OtherActor);
	if (Ball)
	{
		if (OnHit.IsBound())
		{

			OnHit.Broadcast(Player, Ball->Score);
			Ball->Score = 1;
		}
	}
}

// Called when the game starts or when spawned
void APingPongGate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APingPongGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


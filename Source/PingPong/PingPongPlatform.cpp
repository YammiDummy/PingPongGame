// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlatform.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
APingPongPlatform::APingPongPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Platform Body Collider"));
	SetRootComponent(BodyCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);
	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void APingPongPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APingPongPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APingPongPlatform::Server_MoveRight_Validate(float AxisValue)
{
	return true;
}

void APingPongPlatform::Server_MoveRight_Implementation(float AxisValue)
{
	if (AxisValue != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APingPongPlatform::Server_MoveRight_Implementation"));
	}

	FVector CurrentLocation = GetActorLocation();
	FVector NextLocation = GetActorLocation() + GetActorRightVector() * MoveSpeed * AxisValue;

	if(!SetActorLocation(NextLocation, true))
	{
		SetActorLocation(CurrentLocation);
	}
}
 
void APingPongPlatform::Server_RotateRight_Implementation(float AxisValue)
{
	FRotator CurrentRotation = BodyMesh->GetComponentRotation();
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString::Printf(TEXT("y: %f"), FVector::DotProduct(BodyMesh->GetForwardVector(), GetActorForwardVector())), true);

	FRotator NewRotation(0, 0, 0);
	NewRotation.Yaw = CurrentRotation.Yaw + AxisValue;
	if (FVector::DotProduct(BodyMesh->GetForwardVector(), GetActorForwardVector()) > 0.8)
	{

		BodyMesh->SetWorldRotation(NewRotation);
		if (FVector::DotProduct(BodyMesh->GetForwardVector(), GetActorForwardVector()) < 0.8)
		{
			BodyMesh->SetWorldRotation(CurrentRotation);
		}
	}
}

bool APingPongPlatform::Server_RotateRight_Validate(float AxisValue)
{
	return true;
}


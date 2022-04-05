// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"
#include "PingPongPlatform.h"

APingPongPlayerController::APingPongPlayerController()
{
	SetReplicates(true);
}

void APingPongPlayerController::SetStartTransform(FTransform NewStartTransform)
{
	StartTransform = NewStartTransform;
}

void APingPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Move", this, &APingPongPlayerController::MoveRight);
	InputComponent->BindAxis("Rotate", this, &APingPongPlayerController::RotateRight);
}

void APingPongPlayerController::MoveRight(float AxisValue)
{
	if (AxisValue != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::MoveRight"));
	}
	Server_PlatformMoveRight(AxisValue);
}

bool APingPongPlayerController::Server_PlatformMoveRight_Validate(float AxisValue)
{
	return true;
}

void APingPongPlayerController::Server_PlatformMoveRight_Implementation(float AxisValue)
{
	if (Platform)
	{
		if (AxisValue != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation"));
		}

		Platform->Server_MoveRight(AxisValue);
	}

	else
	{
		UE_LOG(LogTemp, Error,TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation: HAS NO PLATFORM!"));
	}
}

bool APingPongPlayerController::Initialize_Validate()
{
	return true;
}

void APingPongPlayerController::Initialize_Implementation()
{
	if (Platform)
	{
		Platform->Destroy();
	}

	SpawnPlatform(PlatformClass);
}

bool APingPongPlayerController::SpawnPlatform_Validate(TSubclassOf<APingPongPlatform> NewPlatformClass)
{
	return NewPlatformClass != NULL;
}

void APingPongPlayerController::SpawnPlatform_Implementation(TSubclassOf<APingPongPlatform> NewPlatformClass)
{
	Platform = (APingPongPlatform*)GetWorld()->SpawnActor<APingPongPlatform>(NewPlatformClass);  //Уточнить у Дениса

	if (Platform)
	{
		Platform->SetActorLocation(StartTransform.GetLocation());
		Platform->SetActorRotation(StartTransform.GetRotation());
	}
}

void APingPongPlayerController::RotateRight(float AxisValue)
{
	if (AxisValue != 0)
	{
		Server_PlatformRotateRight(AxisValue);
	}
}

void APingPongPlayerController::Server_PlatformRotateRight_Implementation(float AxisValue)
{
	if (Platform)
	{
		if (AxisValue != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation"));
		}

		Platform->Server_RotateRight(AxisValue);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation: HAS NO PLATFORM!"));
	}
}

bool APingPongPlayerController::Server_PlatformRotateRight_Validate(float AxisValue)
{
	return true;
}



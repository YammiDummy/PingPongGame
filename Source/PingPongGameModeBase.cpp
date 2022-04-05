// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"

#include "PingPongPlayerPawn.h"
#include "PingPongPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "PingPongGate.h"
#include <Components/BoxComponent.h>
#include "PingPongPlayerStart.h"

APingPongGameModeBase::APingPongGameModeBase()
{
	DefaultPawnClass = APingPongPlayerPawn::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

void APingPongGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CenterPoint = (Player1Start->GetActorLocation() + Player2Start->GetActorLocation()) / 2;

}

void APingPongGameModeBase::AddScore(APingPongPlayerController* Player, float Score)
{
	if (Cast<APingPongPlayerController>(Player))
	{
		if (Player == Player1)
		{
			Player2Score += Score;
		}

		if (Player == Player2)
		{
			Player1Score += Score;
		}
	}
}


void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UWorld* world = GetWorld();
	if (world && (!Player1Start || !Player2Start))
	{
		TArray<AActor*> FoundActors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APingPongPlayerStart::StaticClass(), FoundActors);

		if (FoundActors.Num() > 0) 
		{
			Player1Start = (APingPongPlayerStart*)FoundActors[0];
		}

		if (FoundActors.Num() > 1)
		{
			Player2Start = (APingPongPlayerStart*)FoundActors[1];
		}
	}

	APingPongPlayerController* CurrentPlayer = NULL;
	APingPongPlayerStart* StartPosition = NULL;

	if (Player1 == NULL)
	{
		Player1 = (APingPongPlayerController*)NewPlayer;
		CurrentPlayer = Player1;
		StartPosition = Player1Start;

		if (StartPosition->PingPongGate)
		{
			StartPosition->PingPongGate->Player = CurrentPlayer;
			StartPosition->PingPongGate->OnHit.AddUObject(this, &APingPongGameModeBase::AddScore);
		}
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 1"));
	}

	else if (Player2 == NULL)
	{
		Player2 = (APingPongPlayerController*)NewPlayer;
		CurrentPlayer = Player2;
		StartPosition = Player2Start;

		if (StartPosition->PingPongGate)
		{
			StartPosition->PingPongGate->Player = CurrentPlayer;
			StartPosition->PingPongGate->OnHit.AddUObject(this, &APingPongGameModeBase::AddScore);
		}
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 2"));
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("PingPongGameMode: There are already two players in the game.New connections are not possible"));
		return;
	}

	APingPongPlayerPawn* NewPawn = Cast<APingPongPlayerPawn>(NewPlayer->GetPawn());

	if (!NewPawn)
	{
		NewPawn = world->SpawnActor<APingPongPlayerPawn>(DefaultPawnClass);
	}

	if (StartPosition && NewPawn && Cast<APingPongPlayerController>(NewPlayer))
	{
		NewPawn->SetActorLocation(StartPosition->GetActorLocation());
		NewPawn->SetActorRotation(StartPosition->GetActorRotation());
		NewPlayer->SetPawn(NewPawn);
		CurrentPlayer->SetStartTransform(StartPosition->GetActorTransform());
		CurrentPlayer->Initialize();
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Start position not setted in PingPongGameMode!"));
	}
}

void APingPongGameModeBase::SpawnCoin()
{
	//GetWorld()->SpawnActor()
}

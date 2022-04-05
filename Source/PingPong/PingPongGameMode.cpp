// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"

#include "PingPongPlayerPawn.h"
#include "PingPongPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "PingPongGate.h"
#include <Components/BoxComponent.h>
#include "PingPongPlayerStart.h"

APingPongGameMode::APingPongGameMode()
{
	DefaultPawnClass = APingPongPlayerPawn::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

void APingPongGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (Player1Start && Player2Start)
	{
		CenterPoint = (Player1Start->GetActorLocation() + Player2Start->GetActorLocation()) / 2;
	}
}

void APingPongGameMode::AddScore(APingPongPlayerController* Player, float Score)
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


void APingPongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UWorld* World = GetWorld();
	if (World && (!Player1Start || !Player2Start))
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
			StartPosition->PingPongGate->OnHit.AddUObject(this, &APingPongGameMode::AddScore);
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
			StartPosition->PingPongGate->OnHit.AddUObject(this, &APingPongGameMode::AddScore);
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
		NewPawn = World->SpawnActor<APingPongPlayerPawn>(DefaultPawnClass);
		UE_LOG(LogTemp, Error, TEXT("TEST"));
	}

	if (StartPosition && NewPawn)
	{
		NewPawn->SetActorLocation(StartPosition->GetActorLocation());
		NewPawn->SetActorRotation(StartPosition->GetActorRotation());
		CurrentPlayer->SetPawn(NewPawn);
		CurrentPlayer->SetStartTransform(StartPosition->GetActorTransform());
		CurrentPlayer->Initialize();
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Start position not setted in PingPongGameMode!"));
	}
}

void APingPongGameMode::SpawnCoin()
{
	//GetWorld()->SpawnActor()
}
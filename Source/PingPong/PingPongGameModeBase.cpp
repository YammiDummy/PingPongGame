// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"

#include "PingPongGate.h"
#include "PingPongPlatform.h"
#include "PingPongPlayerPawn.h"
#include "PingPongPlayerStart.h"
#include "PingPongPlayerController.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/InputComponent.h>
#include <Net/UnrealNetwork.h>

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

void APingPongGameModeBase::AddScore(FString Player, float Score)
{
	if (*Player)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%s"), *Player));
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%s"), *Player1->GetName()));
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%s"), *Player2->GetName()));

		if (Player == Player1Name)
		{
			Player2Score += Score;
			OnScoreChanged.Broadcast(Player1Score, Player2Score);
		}

		else if (Player == Player2Name)
		{
			Player1Score += Score;
			OnScoreChanged.Broadcast(Player1Score, Player2Score);
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
		Player1Name = Player1->GetName();

		if (StartPosition->PingPongGate)
		{		
			StartPosition->PingPongGate->Player = CurrentPlayer->GetName();
			StartPosition->PingPongGate->OnHit.AddUObject(this, &APingPongGameModeBase::AddScore);
		}
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 1"));
	}

	else if (Player2 == NULL)
	{
		Player2 = (APingPongPlayerController*)NewPlayer;
		CurrentPlayer = Player2;
		StartPosition = Player2Start;
		Player2Name = Player2->GetName();

		if (StartPosition->PingPongGate)
		{
			StartPosition->PingPongGate->Player = CurrentPlayer->GetName();
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

		if (Player1 == CurrentPlayer)
		{
			Player1Plat = CurrentPlayer->Platform;
		}
		else if (Player2 == CurrentPlayer)
		{
			Player2Plat = CurrentPlayer->Platform;

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("test %s"), *Player2Plat->GetName()));
		}

	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Start position not setted in PingPongGameMode!"));
	}
}

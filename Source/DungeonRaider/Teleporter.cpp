// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include <Kismet/GameplayStatics.h>

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
	//if no actor is set, set the player as the actor to teleport
	CheckActorToTeleportIsValid();

	UE_LOG(LogTemp, Warning, TEXT("Teleporter Actor: %s"), *ActorToTeleport->GetName());
}


void ATeleporter::TeleportActor()
{
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::CheckActorToTeleportIsValid()
{
	if (!ActorToTeleport)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AActor* PlayerActor = reinterpret_cast<AActor*>(PlayerCharacter);
		ActorToTeleport = PlayerActor;
	}
}



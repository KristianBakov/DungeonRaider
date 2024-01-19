// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

}


void ATeleporter::TeleportActor(AActor* ActorToTeleport)
{
	if (!DestinationTeleporter) return;
	FVector Origin, Box;
	ActorToTeleport->GetActorBounds(false, Origin, Box, false);
	FVector TeleportOffset = Origin + TeleportOffsetConst;
	UE_LOG(LogTemp, Warning, TEXT("Teleporting %s by %s"), *ActorToTeleport->GetName(), *TeleportOffset.ToString());
	ActorToTeleport->SetActorLocation(DestinationTeleporter->GetActorLocation() + FVector(0,0, TeleportOffset.Z));
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





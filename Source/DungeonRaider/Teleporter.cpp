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
	ActorToTeleport->SetActorLocation(DestinationTeleporter->GetActorLocation() + TeleportOffset);
	//log lovation
UE_LOG(LogTemp, Warning, TEXT("Teleporting %s to %s"), *ActorToTeleport->GetName(), *DestinationTeleporter->GetActorLocation().ToString());
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





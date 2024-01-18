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


void ATeleporter::TeleportActor()
{
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include <Kismet/GameplayStatics.h>
#include "Grabber.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = reinterpret_cast<AActor*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ATeleporter::CalculateTeleportOffset(AActor* ActorToTeleport, FVector& OutTeleportOffset)
{
	FVector Origin, Box;
	ActorToTeleport->GetActorBounds(false, Origin, Box, false);
	OutTeleportOffset = Origin + TeleportOffsetConst;
}

void ATeleporter::FindAndReleaseGrabber()
{
	if (PlayerCharacter)
	{
		UGrabber* Grabber = PlayerCharacter->FindComponentByClass<UGrabber>();
		if (Grabber)
		{
			Grabber->Release();
		}
	}
}

void ATeleporter::OnTeleportComplete()
{
	if (ActorToTelportRootComponent)
	{
		ActorToTelportRootComponent->SetSimulatePhysics(true);
		IsTeleporting = false;
	}
}

void ATeleporter::FreezeTeleportActorForDelay()
{
	ActorToTelportRootComponent->SetSimulatePhysics(false);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATeleporter::OnTeleportComplete, TeleportDelay, false);
}


bool ATeleporter::SetActorToTeleportRootComponent(AActor* ActorToTeleport)
{
	ActorToTelportRootComponent = Cast<UPrimitiveComponent>(ActorToTeleport->GetRootComponent());
	if (!ActorToTelportRootComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor to teleport has no root component"));
		return false;
	}
	return true;
}

void ATeleporter::TeleportActor(AActor* ActorToTeleport)
{
	if (!DestinationTeleporter) return;
	if (!SetActorToTeleportRootComponent(ActorToTeleport)) return;

	IsTeleporting = true;
	FindAndReleaseGrabber();

	//set location
	FVector TeleportOffset;
	CalculateTeleportOffset(ActorToTeleport, TeleportOffset);
	ActorToTeleport->SetActorLocation(DestinationTeleporter->GetActorLocation() + FVector(0,0, TeleportOffset.Z));

	if (ActorToTeleport == PlayerCharacter) return;
	FreezeTeleportActorForDelay();
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





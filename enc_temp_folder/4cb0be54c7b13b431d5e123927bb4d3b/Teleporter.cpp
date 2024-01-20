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

}

void ATeleporter::CalculateTeleportOffset(AActor* ActorToTeleport, FVector& OutTeleportOffset)
{
	FVector Origin, Box;
	ActorToTeleport->GetActorBounds(false, Origin, Box, false);
	OutTeleportOffset = Origin + TeleportOffsetConst;
}

void ATeleporter::FindAndReleaseGrabber()
{
	AActor* PlayerCharacter = reinterpret_cast<AActor*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UGrabber* Grabber = PlayerCharacter->FindComponentByClass<UGrabber>();
		if (Grabber)
		{
			Grabber->Release();
		}
	}
}


void ATeleporter::TeleportActor(AActor* ActorToTeleport)
{
	if (!DestinationTeleporter) return;
	ActorToTeleportRef = ActorToTeleport;

	IsTeleporting = true;
	FindAndReleaseGrabber();

	FVector TeleportOffset;
	CalculateTeleportOffset(ActorToTeleport, TeleportOffset);
	ActorToTeleport->SetActorLocation(DestinationTeleporter->GetActorLocation() + FVector(0,0, TeleportOffset.Z));

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {IsTeleporting = false; }, TeleportDelay, false);
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTeleporting)
	{
		UPrimitiveComponent* ActorToTelportRootComponent = Cast<UPrimitiveComponent>(ActorToTeleportRef->GetRootComponent());
		if (ActorToTelportRootComponent)
		{
			ActorToTelportRootComponent->SetSimulatePhysics(false);
		}
		else
		{
			ActorToTelportRootComponent->SetSimulatePhysics(true);
		}
	}
}





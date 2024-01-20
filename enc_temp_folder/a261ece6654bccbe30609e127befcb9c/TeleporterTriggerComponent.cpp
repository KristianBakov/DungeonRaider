// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleporterTriggerComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Teleporter.h"

UTeleporterTriggerComponent::UTeleporterTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTeleporterTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTeleporterTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	this->OnComponentBeginOverlap.AddDynamic(this, &UTeleporterTriggerComponent::OnOverlapBegin);

	//if no actor set through BP, set it to the player by default
	CheckActorToTeleportIsValid();
}

void UTeleporterTriggerComponent::CheckActorToTeleportIsValid()
{
	if (!ActorToTeleport)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AActor* PlayerActor = reinterpret_cast<AActor*>(PlayerCharacter);
		ActorToTeleport = PlayerActor;
	}
}


void UTeleporterTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ActorToTeleport)
	{

		//get owner as teleporter
		ATeleporter* Owner = reinterpret_cast<ATeleporter*>(GetOwner());
		if(Owner)
		{
			UE_LOG(LogTemp, Warning, TEXT("Teleporting %s"), *OtherActor->GetName());
			Owner->TeleportActor(ActorToTeleport);
		}
	}
}

void UTeleporterTriggerComponent::SetTriggerActor(AActor* ActorIn)
{
	ActorToTeleport = ActorIn;
}

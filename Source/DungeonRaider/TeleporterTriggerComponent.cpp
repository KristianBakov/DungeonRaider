// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleporterTriggerComponent.h"
#include <Kismet/GameplayStatics.h>

UTeleporterTriggerComponent::UTeleporterTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTeleporterTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	this->OnComponentBeginOverlap.AddDynamic(this, &UTeleporterTriggerComponent::OnOverlapBegin);
}

void UTeleporterTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

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
	UE_LOG(LogTemp, Warning, TEXT("Actor to teleport is %s"), *ActorToTeleport->GetName());
}


void UTeleporterTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap begin"));
}

void UTeleporterTriggerComponent::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}

void UTeleporterTriggerComponent::SetTriggerActor(AActor* ActorIn)
{
	ActorToTeleport = ActorIn;
}

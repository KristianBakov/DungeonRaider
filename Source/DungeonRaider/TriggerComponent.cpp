// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	AActor* UnlockableActor = GetUnlockableActor();
	if (UnlockableActor)
	{
		UPrimitiveComponent* UnlockableActorRootComponent =  Cast<UPrimitiveComponent>(UnlockableActor->GetRootComponent());
		if (UnlockableActorRootComponent)
		{
			UnlockableActorRootComponent->SetSimulatePhysics(false);
		}
		UnlockableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* MoverIn)
{
	Mover = MoverIn;
}

AActor* UTriggerComponent::GetUnlockableActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		bool HasUnlockableTag = OverlappingActor->ActorHasTag(UnlockableTag);
		bool IsGrabbed = OverlappingActor->ActorHasTag("Grabbed");
		if (HasUnlockableTag && !IsGrabbed)
		{
			return OverlappingActor;
		}
	}
	return nullptr;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TriggerComponent BeginPlay has been called"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	AActor* UnlockableActor = GetUnlockableActor();
	if (UnlockableActor)
	{
		UPrimitiveComponent* ThisRootComponent =  Cast<UPrimitiveComponent>(UnlockableActor->GetRootComponent());
		if (ThisRootComponent)
		{
			ThisRootComponent->SetSimulatePhysics(false);
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
		if (OverlappingActor->ActorHasTag(UnlockableTag))
		{
			return OverlappingActor;
		}
	}
	return nullptr;
}

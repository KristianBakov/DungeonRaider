// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleporterTriggerComponent.h"

UTeleporterTriggerComponent::UTeleporterTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTeleporterTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTeleporterTriggerComponent::SetTriggerActor(AActor* ActorIn)
{
}

void UTeleporterTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

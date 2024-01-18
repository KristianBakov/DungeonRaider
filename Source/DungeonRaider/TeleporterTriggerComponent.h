// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerComponent.h"
#include "TeleporterTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONRAIDER_API UTeleporterTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UTeleporterTriggerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void SetTriggerActor(AActor* ActorIn);

protected:
	virtual void BeginPlay() override;
};

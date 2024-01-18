// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class DUNGEONRAIDER_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleporter();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere)
	ATeleporter* DestinationTeleporter;

	UPROPERTY(EditAnywhere)
	float TeleportDelay = 1.0f;

	bool IsTeleporting = false;

	void TeleportActor();

};

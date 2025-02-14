// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/Delegate.h"
#include "Teleporter.generated.h"

DECLARE_MULTICAST_DELEGATE(FTeleportDelegate);

UCLASS()
class DUNGEONRAIDER_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleporter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Teleporter")
	void TeleportActor(AActor* ActorToTeleport);



protected:
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere)
	ATeleporter* DestinationTeleporter;
	AActor* ActorToTeleportRef;

	const FVector TeleportOffsetConst = FVector(0.0f, 0.0f, 50.0f);
	void CalculateTeleportOffset(AActor* ActorToTeleport, FVector& OutTeleportOffset);
	void FindAndReleaseGrabber();

	UPROPERTY(EditAnywhere)
	float TeleportDelay = 3.0f;

	bool IsTeleporting = false;

};

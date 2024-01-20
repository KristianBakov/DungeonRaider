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
	UPrimitiveComponent* ActorToTelportRootComponent;

	const FVector TeleportOffsetConst = FVector(0.0f, 0.0f, 50.0f);
	bool SetActorToTeleportRootComponent(AActor* ActorToTeleport);
	void CalculateTeleportOffset(AActor* ActorToTeleport, FVector& OutTeleportOffset);
	void FindAndReleaseGrabber();
	void OnTeleportComplete();
	void FreezeTeleportActorForDelay();

	UPROPERTY(EditAnywhere)
	float TeleportDelay = 1.0f;

	bool IsTeleporting = false;

};

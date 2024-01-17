// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!GetPhysicsHandleComponent()) return;
	if (!GetPhysicsHandleComponent()->GrabbedComponent) return;
	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	GetPhysicsHandleComponent()->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabber::Release()
{
	if(!GetPhysicsHandleComponent()) return;

	if(GetPhysicsHandleComponent()->GrabbedComponent)
	{
		GetPhysicsHandleComponent()->ReleaseComponent();
	}
}

void UGrabber::Grab()
{
	if(!GetPhysicsHandleComponent()) return;

	FHitResult OutHitResult;
	if (GetGrabbableInReach(OutHitResult))
	{
		UPrimitiveComponent* HitComponent = OutHitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		GetPhysicsHandleComponent()->GrabComponentAtLocationWithRotation(HitComponent, NAME_None,
			OutHitResult.ImpactPoint, GetComponentRotation());
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& HitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(HitResult, Start, End,
		FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandleComponent() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"


void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}

ASItemChest::ASItemChest(): TargetPitch(110.f)
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(RootComponent);
}


void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}


void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

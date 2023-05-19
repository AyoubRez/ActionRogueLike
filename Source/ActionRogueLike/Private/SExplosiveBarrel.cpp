// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "SMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"

ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionProfileName("PhysicsActor");

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 700.0f;
	RadialForceComp->ImpulseStrength = 500.0f;
	RadialForceComp->bImpulseVelChange = true;
}

void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);
}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	if (ASMagicProjectile* MagicProjectile = Cast<ASMagicProjectile>(OtherActor))
	{
		RadialForceComp->FireImpulse();
	}
}


void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

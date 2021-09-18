// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	//Dynamic Binding 
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);

	// Since this does not have a transform, it does not need to set somewhere in the component hirearchy. 
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	// This is how long the object will live, once this time is up the destructor will be invoked.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned.
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//this plays the launch sound with 3d audio at the location of spawn
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

	AActor* MyOwner = GetOwner();

	// If the owner does not exist get out of the function.
	if (MyOwner == nullptr)
	{
		return;
	}

	if (OtherActor != nullptr && OtherActor != this && OtherActor != MyOwner)
	{
		// For this function ApplyDamage, you have to give it a AController (see function).
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		Destroy();
	}

	// TODO : implement explosion sound and particle effects 

}
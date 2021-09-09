// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/BoxComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setting capsule comp as the root component of the object
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule Collider"));
	RootComponent = BoxComp;

	//setting BaseMesh as a child component of CapsuleComp
	BaseMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	//setting TurretMesh as a child of BaseMesh
	TurretMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	//setting ProjectileSpawnPoint as a child of TurretMesh
	ProjectileSpawnPoint = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurretFunction(FVector LookAtTarget)
{
	//Update Turret Mesh rotation to face towards the LookAtTarget passed in from Child Classes.
	//TurretMesh->SetWorldRotation() 

}

void APawnBase::Fire()
{
	//Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation
}

void APawnBase::HandleDestruction()
{
	// Universal Functionality
	//play death effects particle, sound and camera shake

	// Then do child overrides
	//	-pawn turret inform gamemode that turret died then destroy() self.

	//	-pawn tank inform gamemode player died -> then hide() all components && stop movement input 


}






// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapon/WeaponBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ShapeComponent.h"

// Sets default values
AWeaponBullet::AWeaponBullet()
{
	collisionComp_ = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	collisionComp_->InitSphereRadius(5.0f);
	collisionComp_->BodyInstance.SetCollisionProfileName("Projectile");
	collisionComp_->OnComponentHit.AddDynamic(this, &AWeaponBullet::OnHit);

	collisionComp_->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//캐릭터 탑승 가능여부
	collisionComp_->CanCharacterStepUpOn = ECB_No;
	
	//BulletMesh
	bulletMesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BULLETMESH"));
	RootComponent = collisionComp_;
	bulletMesh_->SetupAttachment(collisionComp_);

	//StaticMesh
	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> BULLET_MESH(TEXT("/Game/StartPack/StartPack/ThirdPerson/Meshes/RightArm_StaticMesh.RightArm_StaticMesh"));

	if (BULLET_MESH.Succeeded())
	{
		bulletMesh_->SetSkeletalMesh(BULLET_MESH.Object);
		ABLOG(Warning, TEXT("Succeess : BulletMesh"));
	}
	bulletMesh_->SetCollisionProfileName(TEXT("NoCollision"));*/
	
	
	



	projectileMovement_ = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILECOMP"));
	projectileMovement_->UpdatedComponent = collisionComp_;
	projectileMovement_->InitialSpeed = 3000.0f;
	projectileMovement_->MaxSpeed = 3000.0f;
	projectileMovement_->bRotationFollowsVelocity = true;
	projectileMovement_->bShouldBounce = true;

	InitialLifeSpan = 3.0f;
}

void AWeaponBullet::OnHit(UPrimitiveComponent* _hitComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, FVector _normalImpules, const FHitResult& _hit)
{
	if ((_otherActor != NULL) && (_otherActor != this) && (_otherComp != NULL) && _otherComp->IsSimulatingPhysics())
	{
		_otherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}
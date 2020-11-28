#include "Projectile.h"


#include "Voxels/VoxelsGameModeBase.h"
#include "Voxels/Common/Coordinates.h"
#include "Voxels/World/Chunk.h"

AProjectile::AProjectile()
{
    Sphere = CreateDefaultSubobject<USphereComponent>(FName("SphereCollider"));
    //Sphere->SetSimulatePhysics(true);
    FBodyInstance& Body = Sphere->BodyInstance;
    Body.bNotifyRigidBodyCollision = true;
    Body.SetCollisionProfileName(TEXT("Projectile"));
    /*Body.SetEnableGravity(false);
    Body.SetInstanceSimulatePhysics(true);*/
    Sphere->OnComponentHit.AddDynamic(this, &AProjectile::OnStop);
    Movement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
    Movement->SetUpdatedComponent(Sphere);
    Movement->bRotationFollowsVelocity = true;
    Movement->bShouldBounce = false;
    RootComponent = Sphere;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    Sphere->InitSphereRadius(ProjectileSize);
    Movement->MaxSpeed = DefaultSpeed;
    Movement->InitialSpeed = DefaultSpeed;
}

void AProjectile::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AProjectile::Shoot(const FVector& Direction) const
{
    Movement->Velocity = Direction * Movement->InitialSpeed;
}


void AProjectile::OnStop(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComponent,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    AChunk* Chunk = Cast<AChunk>(Hit.Actor);
    if (Chunk == nullptr)
    {
        return;
    }
    TBlockBuffer& Blocks = Chunk->GetBlocks();
    FVector BlockPos = Hit.Location + (Hit.Normal * 0.2F);
    FIntVector Vector = VectorToGlobal(BlockPos);
    //TODO: This is server only, we need to create a ChunkManager and find a way to set that to a singleton
    const FIntVector Local = ToLocal(Vector);
    Blocks[IndexOf(Local.X, Local.Y, Local.Z)] = FBlocks::Empty;
    Chunk->SetChunkFlags(static_cast<EChunkFlag>(0));
    Destroy();
}

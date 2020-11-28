#pragma once
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile.generated.h"

UCLASS()
class AProjectile final : public AActor
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
    UProjectileMovementComponent* Movement;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
    float ProjectileSize;
    UPROPERTY(BlueprintReadOnly, Meta=(AllowPrivateAccess=true))
    USphereComponent* Sphere;
private:
    void OnStop(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
public:

    AProjectile();
    virtual void Tick(float DeltaSeconds) override;
    void Shoot(const FVector& Direction) const;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefaultSpeed = 5000.0F;

protected:
    virtual void BeginPlay() override;

public:
    UProjectileMovementComponent* GetMovement()
    {
        return Movement;
    }
};

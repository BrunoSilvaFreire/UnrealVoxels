#pragma once

#include "WorldGenerator.h"
#include "IslandWorldGenerator.generated.h"
UCLASS()
class UIslandWorldGenerator final : public UWorldGenerator
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    UCurveFloat* xMax;
    UPROPERTY(EditAnywhere)
    UCurveFloat* xMin;
    UPROPERTY(EditAnywhere)
    UCurveFloat* yMax;
    UPROPERTY(EditAnywhere)
    UCurveFloat* yMin;
    virtual void Populate(TBlockBuffer& buffer, const FIntPoint position) override;
};

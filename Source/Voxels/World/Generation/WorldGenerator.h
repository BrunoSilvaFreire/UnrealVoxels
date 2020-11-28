#pragma once
#include <Voxels/World/Block.h>
#include "WorldGenerator.generated.h"

UCLASS(Abstract)
class UWorldGenerator : public UDataAsset
{
    GENERATED_BODY()
public:
    virtual ~UWorldGenerator() = default;

    virtual void Populate(TBlockBuffer& buffer, const FIntPoint position)
    {
    };
};

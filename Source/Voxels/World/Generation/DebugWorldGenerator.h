#pragma once
#include "WorldGenerator.h"
#include "DebugWorldGenerator.generated.h"

UCLASS()
class UDebugWorldGenerator : public UWorldGenerator
{
    GENERATED_BODY()
public:
    virtual void Populate(TBlockBuffer& buffer, const FIntPoint position) override;
};

#pragma once
#include "WorldGenerator.h"
#include "RandomWorldGenerator.generated.h"
UCLASS()
class URandomWorldGenerator : public UWorldGenerator
{
    GENERATED_BODY()
public:
    virtual void Populate(TBlockBuffer& buffer, const FIntPoint position) override;
};

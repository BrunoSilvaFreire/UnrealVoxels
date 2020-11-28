#pragma once
#include <Voxels/World/Chunk.h>
#include "DebuggableChunk.generated.h"

UCLASS()
class ADebuggableChunk : public AChunk
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    UWorldGenerator* WorldGenerator;
protected:
    virtual void BeginPlay() override;
public:
    virtual void Tick(float DeltaTime) override;
};

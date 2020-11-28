// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Voxels/World/Chunk.h>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "World/ChunkManager.h"

#include "VoxelsGameModeBase.generated.h"
UCLASS()
class VOXELS_API AVoxelsGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
private:
    UChunkManager* ChunkManager;

public:
    AVoxelsGameModeBase();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Voxels)
    UWorldGenerator* WorldGenerator;

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = Voxels
    )
    uint8 MapSize;

protected:
    virtual void BeginPlay() override;
};

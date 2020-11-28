// Copyright Epic Games, Inc. All Rights Reserved.


#include "VoxelsGameModeBase.h"

#include <Voxels/Common/Coordinates.h>


AVoxelsGameModeBase::AVoxelsGameModeBase()
{
}

void AVoxelsGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    ChunkManager = new UChunkManager(GetWorld(), WorldGenerator);
    // Generate one more so that edge chunks are ok
    uint8 Radius = MapSize + 1;
    UE_LOG(LogTemp, Warning, TEXT("Generating world @ radius %d"), Radius);
    for (int x = -Radius; x <= Radius; ++x)
    {
        for (int y = -Radius; y <= Radius; ++y)
        {
            ChunkManager->GetChunk(FIntPoint(x, y));
        }
    }
}

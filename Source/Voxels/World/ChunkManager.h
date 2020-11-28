#pragma once
#include "CoreMinimal.h"
#include <Voxels/World/Chunk.h>


class UChunkManager  
{
private:
    UWorld * World;
    UWorldGenerator* Generator;
    TMap<FIntPoint, AChunk*> ChunkCache;
    AChunk* LoadChunk(FIntPoint Point, bool Generate = true);
public:
    UChunkManager(UWorld* World, UWorldGenerator* Generator);

    TMap<FIntPoint, AChunk*>& GetChunkCache();
    AChunk* GetChunk(FIntPoint Coordinate, bool Load = true);
    void SetBlock(const FIntVector& Vector, const FBlock& Block);
};

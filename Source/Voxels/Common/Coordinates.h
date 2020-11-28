#pragma once
#include "HAL/Platform.h"
#include "Math/IntVector.h"
#include <Voxels/Voxels.h>

inline size_t IndexOf(const uint8 x, const uint8 y, const uint8 z)
{
    return x + FVoxels::ChunkSize * y + z * FVoxels::ChunkArea;
}


FIntVector ToLocal(const FIntVector& Global);
FIntVector ToGlobal(const FIntVector& Local, const FIntPoint& Chunk);
FIntPoint GlobalBlockToChunk(const FIntVector& Position);
int ToGlobal(int Local, int Chunk);
FIntVector VectorToGlobal(const FVector& Vector);

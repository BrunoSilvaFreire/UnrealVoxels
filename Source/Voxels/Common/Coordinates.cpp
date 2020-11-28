#include "Coordinates.h"
#include <Voxels/Voxels.h>

int InternalMod(int a, int b)
{
    return (b + (a % b)) % b;
}

FIntVector ToLocal(const FIntVector& Global)
{
    return FIntVector(
        InternalMod(Global.X, FVoxels::ChunkSize),
        InternalMod(Global.Y, FVoxels::ChunkSize),
        Global.Z
    );
}

FIntVector ToGlobal(const FIntVector& Local, const FIntPoint& Chunk)
{
    return FIntVector(
        Local.X + (Chunk.X * FVoxels::ChunkSize),
        Local.Y + (Chunk.Y * FVoxels::ChunkSize),
        Local.Z
    );
}

int ToGlobal(int Local, int Chunk)
{
    return Local + (Chunk * FVoxels::ChunkSize);
}

FIntPoint GlobalBlockToChunk(const FIntVector& Position)
{
    return FIntPoint(
        Position.X / FVoxels::ChunkSize,
        Position.Y / FVoxels::ChunkSize
    );
}

FIntVector VectorToGlobal(const FVector& Vector)
{
    return FIntVector(
        FMath::FloorToInt(Vector.X),
        FMath::FloorToInt(Vector.Y),
        Vector.Z
    );
}

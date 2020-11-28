#pragma once
#include <Voxels/Voxels.h>

enum EBlockFlags : uint8
{
    Opaque = 1 << 0,
    Indestructible = 1 << 1,
    DamageHighestBit = 1 << 6,
    DamageLowestBit = 1 << 7
};

struct FBlock
{
    explicit FBlock(const EBlockFlags& Flags) : Flags(Flags)
    {
    }

    FBlock() = default;

    EBlockFlags Flags;
};

class FBlocks
{
public:

    static const FBlock Empty;
};

typedef TArray<FBlock, TFixedAllocator<FVoxels::ChunkVolume>> TBlockBuffer;

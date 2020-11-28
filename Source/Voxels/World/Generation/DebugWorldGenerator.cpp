#include "DebugWorldGenerator.h"
#include <Voxels/Common/Coordinates.h>

void UDebugWorldGenerator::Populate(TBlockBuffer& buffer, const FIntPoint position)
{
    uint8 ChunkBase = position.X % 2 == 0 && position.Y % 2 == 0 ? 3 : 5;
    for (uint8 x = 0; x < FVoxels::ChunkSize; ++x)
    {
        for (uint8 y = 0; y < FVoxels::ChunkSize; ++y)
        {
            const int min = ChunkBase + FGenericPlatformMath::Min(x, y);
            for (uint8 z = 0; z < FVoxels::ChunkHeight; ++z)
            {
                size_t i = IndexOf(x, y, z);
                FBlock Block;
                if (z <= min)
                {
                    Block.Flags = EBlockFlags::Opaque;
                }
                else
                {
                    Block.Flags = static_cast<EBlockFlags>(0);
                }
                buffer[i] = Block;
            }
        }
    }
}

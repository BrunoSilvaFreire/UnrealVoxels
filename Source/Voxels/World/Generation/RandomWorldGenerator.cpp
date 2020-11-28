#include "RandomWorldGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Voxels/Common/Coordinates.h"

void URandomWorldGenerator::Populate(TBlockBuffer& buffer, const FIntPoint position)
{
    for (uint8 x = 0; x < FVoxels::ChunkSize; ++x)
    {
        for (uint8 y = 0; y < FVoxels::ChunkSize; ++y)
        {
            for (uint8 z = 0; z < FVoxels::ChunkHeight; ++z)
            {
                const size_t i = IndexOf(x, y, z);
                FBlock Block;
                if (FGenericPlatformMath::FRand() > 0.5F)
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

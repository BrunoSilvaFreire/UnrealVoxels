#include "IslandWorldGenerator.h"
#include <Voxels/Common/Coordinates.h>

bool IsWithin(float Value, float Min, float Max)
{
    return Value > Min && Value < Max;
}

void UIslandWorldGenerator::Populate(TBlockBuffer& buffer, const FIntPoint position)
{
    int MapWidthInBlocks = FVoxels::ChunkSize * ((FVoxels::MapSize * 2) + 1);
    int BlockBase = -(MapWidthInBlocks / 2);
    UE_LOG(LogTemp, Display, TEXT("Populating %d, %d"), position.X, position.Y);
    UE_LOG(LogTemp, Warning, TEXT("Block Base %d, Map Width %d"), BlockBase, MapWidthInBlocks);
    for (int x = 0; x < FVoxels::ChunkSize; ++x)
    {
        int BlockX = ToGlobal(x, position.X) - BlockBase;
        const float TimeX = FMath::Clamp(static_cast<float>(BlockX) / MapWidthInBlocks, 0.0F, 1.0F);
        const float MaxX = xMax->GetFloatValue(TimeX);
        const float MinX = xMin->GetFloatValue(TimeX);
        for (int y = 0; y < FVoxels::ChunkSize; ++y)
        {
            int BlockY = ToGlobal(y, position.Y) - BlockBase;
            const float TimeY = FMath::Clamp(static_cast<float>(BlockY) / MapWidthInBlocks, 0.0F, 1.0F);
            const float MaxY = xMax->GetFloatValue(TimeY);
            const float MinY = xMin->GetFloatValue(TimeY);
            const float Min = MinX * MinY;
            const float Max = MaxX * MaxY;
            for (int z = 0; z < FVoxels::ChunkHeight; ++z)
            {
                const float ZValue = static_cast<float>(z) / FVoxels::ChunkHeight;
                const size_t i = IndexOf(x, y, z);
                const float Perlin = FMath::PerlinNoise3D(FVector(TimeX, TimeY, ZValue));
                const float FinalValue = ZValue + (-1.0F + Perlin * 2) * 0.2F;

                FBlock Block;
                if (IsWithin(ZValue, Min, Max))
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

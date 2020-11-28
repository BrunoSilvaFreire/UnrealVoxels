#include "DebuggableChunk.h"

#include "DrawDebugHelpers.h"
#include <Voxels/Common/Coordinates.h>

void ADebuggableChunk::BeginPlay()
{
    Super::BeginPlay();
    Populate(WorldGenerator);
    for (uint8 x = 0; x < FVoxels::ChunkSize; ++x)
    {
        for (uint8 y = 0; y < FVoxels::ChunkSize; ++y)
        {
            for (uint8 z = 0; z < FVoxels::ChunkHeight; ++z)
            {
                FVector pos = GetTransform().GetLocation();
                FVector blockLocalPos(x, y, z);
                FVector labelPos = pos + blockLocalPos * 32;
                FString str;
                str.Append("(");
                str.AppendInt(x);
                str.Append(", ");
                str.AppendInt(y);
                str.Append(", ");
                str.AppendInt(z);
                str.Append(" @ ");
                str.AppendInt(IndexOf(x, y, z));
                str.Append(")");
                DrawDebugString(GetWorld(), labelPos, str);
            }
        }
    }
}

void ADebuggableChunk::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

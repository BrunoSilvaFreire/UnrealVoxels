#include "GenerationJob.h"


#include <Voxels/Common/BlockFace.h>
#include <Voxels/Common/Coordinates.h>
#include <Voxels/Voxels.h>
#include <Voxels/World/Chunk.h>
#include <Voxels/Common/Masking.h>


FGenerationJob::FGenerationJob(AChunk* Chunk) : Chunk(Chunk)
{
}

FGenerationJob::~FGenerationJob()
{
}

bool IsOutOfAxisBounds(int pos)
{
    return pos < 0 || pos >= FVoxels::ChunkSize;
}

bool IsOutOfHeightBounds(int pos)
{
    return pos < 0 || pos >= FVoxels::ChunkHeight;
}

bool IsOutOfBounds(FIntVector pos)
{
    return IsOutOfAxisBounds(pos.X) || IsOutOfAxisBounds(pos.Y);
}

void FGenerationJob::DoWork()
{
    UProceduralMeshComponent* staticMesh = Chunk->GetMeshComponent();
    if (staticMesh == nullptr)
    {
        return;
    }
    const FChunkNeighbor& Neighbors = Chunk->GetNeighbors();

    TBlockBuffer& Buf = Chunk->GetBlocks();
    for (int x = 0; x < FVoxels::ChunkSize; ++x)
    {
        for (int y = 0; y < FVoxels::ChunkSize; ++y)
        {
            for (int z = 0; z < FVoxels::ChunkHeight; ++z)
            {
                size_t i = IndexOf(x, y, z);
                FBlock& Block = Buf[i];
                if (!IsSet(Block.Flags, EBlockFlags::Opaque))
                {
                    //Air block
                    continue;
                }
                for (const FBlockFace Face : FBlockFace::Faces)
                {
                    FIntVector AdjPos = Face.Direction;
                    AdjPos.X += x;
                    AdjPos.Y += y;
                    AdjPos.Z += z;
                    FIntVector BlockPos;
                    TBlockBuffer* ToAccess;
                    if (IsOutOfBounds(AdjPos))
                    {
                        BlockPos = ToLocal(AdjPos);
                        const FIntVector Dir = Face.Direction;
                        const uint8 NeighborIndex = FChunkNeighbor::IndexOf(FIntPoint(Dir.X, Dir.Y));
                        AChunk* Other = Neighbors.Chunks[NeighborIndex];
                        if (Other == nullptr)
                        {
                            continue;
                        }
                        const EChunkFlag OtherFlags = Other->GetChunkFlags();
                        if ((OtherFlags & EChunkFlag::Populated) != EChunkFlag::Populated)
                        {
                            continue;
                        }
                        ToAccess = &Other->GetBlocks();
                    }
                    else
                    {
                        BlockPos = AdjPos;
                        ToAccess = &Buf;
                    }
                    // If out of height bounds, draw anyway
                    if (!IsOutOfHeightBounds(BlockPos.Z))
                    {
                        const size_t BlockIndex = IndexOf(BlockPos.X, BlockPos.Y, BlockPos.Z);
                        // Block is also empty?

                        if (IsSet(ToAccess->operator[](BlockIndex).Flags, EBlockFlags::Opaque))
                        {
                            continue;
                        }
                    }
                    BuildFace(FVector(x, y, z), Face);
                }
            }
        }
    }

    TArray<FProcMeshTangent> Tangents;
    TArray<FColor> Colors;
    TArray<FVector2D> UV0;
    staticMesh->CreateMeshSection(1, Vertices, Indices, Normals, UV0, Colors, Tangents, true);
    staticMesh->SetMobility(EComponentMobility::Static);
    staticMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
    Chunk->SetChunkFlags(EChunkFlag::Populated);
}


void FGenerationJob::BuildFace(const FVector& Position, const FBlockFace& Face)
{
    const FVector Center = Position + FVector(.5f);
    const FVector Normal = static_cast<FVector>(Face.Direction);
    const FVector& Up = Face.Up;
    const FVector& Right = Face.Right;
    const FVector Front = Center + Normal * .5f;
    const size_t Start = Vertices.Num();
    Vertices.Reserve(Start + 4);
    Vertices.Emplace(Front + (Right + Up) * .5f);
    Vertices.Emplace(Front + (-Right + Up) * .5f);
    Vertices.Emplace(Front + (Right + -Up) * .5f);
    Vertices.Emplace(Front + (-Right + -Up) * .5f);
    Normals.Emplace(Normal);
    Normals.Emplace(Normal);
    Normals.Emplace(Normal);
    Normals.Emplace(Normal);

    Indices.Reserve(Indices.Num() + 4);
    Indices.Add(Start + 0);
    Indices.Add(Start + 1);
    Indices.Add(Start + 2);
    Indices.Add(Start + 3);
    Indices.Add(Start + 2);
    Indices.Add(Start + 1);
}

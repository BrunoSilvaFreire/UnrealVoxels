#include "ChunkManager.h"
#include "Engine/World.h"

#include "Voxels/Common/Coordinates.h"

TMap<FIntPoint, AChunk*>& UChunkManager::GetChunkCache()
{
    return ChunkCache;
}

AChunk* UChunkManager::LoadChunk(FIntPoint Coordinate, bool Generate)
{
    int x = Coordinate.X;
    int y = Coordinate.Y;
    const float xF = static_cast<float>(x * FVoxels::Scale * FVoxels::ChunkSize);
    const float yF = static_cast<float>(y * FVoxels::Scale * FVoxels::ChunkSize);
    // UE_LOG(LogTemp, Warning, TEXT("Creating %d, %d (%f, %f)"), x, y, xF, yF);
    const FVector Position(xF, yF, 0);
    FActorSpawnParameters Parameters;
    FString ChunkName;
    ChunkName.Append("Chunk (");
    ChunkName.AppendInt(x);
    ChunkName.Append(", ");
    ChunkName.AppendInt(y);
    ChunkName.Append(")");
    Parameters.Name = FName(*ChunkName);
    AChunk* Chunk = World->SpawnActor<AChunk>(Position, FRotator(0), Parameters);
    Chunk->SetActorScale3D(FVector(FVoxels::Scale));
    Chunk->SetChunkPosition(Coordinate);
    if (Generate)
    {
        Chunk->SetChunkFlags(EChunkFlag::Dirty);
    }
    Chunk->Populate(Generator);

    auto& Neighbors = Chunk->GetNeighbors();
    FIntPoint Adjacents[] = {
        FIntPoint(1, 0),
        FIntPoint(-1, 0),
        FIntPoint(0, 1),
        FIntPoint(0, -1)
    };
    ChunkCache.Add(Coordinate, Chunk);
    for (FIntPoint Adjacent : Adjacents)
    {
        const FIntPoint NeighborCoord = Coordinate + Adjacent;
        AChunk** NeighborPtr = ChunkCache.Find(NeighborCoord);
        if (NeighborPtr == nullptr)
        {
            continue;
        }
        AChunk* Neighbor = *NeighborPtr;
        uint8 NeighborIndex = FChunkNeighbor::IndexOf(Adjacent);
        if (NeighborIndex > 4)
        {
            /*UE_LOG(LogTemp, Warning, TEXT("Invalid neighbor index at %d (%d, %d)"), NeighborIndex, Adjacent.X,
            Adjacent.Y);*/
        }
        Neighbors.Chunks[NeighborIndex] = Neighbor;
        /*UE_LOG(LogTemp, Display, TEXT("Found neighbor %d (%d, %d)"), NeighborIndex, Adjacent.X,
        Adjacent.Y);*/
        FIntPoint OppositeAdj = Adjacent * -1;
        uint8 OppositeIndex = FChunkNeighbor::IndexOf(OppositeAdj);
        if (OppositeIndex >= 4)
        {
            /*UE_LOG(LogTemp, Warning, TEXT("Invalid opposite index at %d (%d, %d)"), OppositeIndex, OppositeAdj.X,
            OppositeAdj.Y);*/
        }
        /*UE_LOG(LogTemp, Display, TEXT("Found neighbor %d (%d, %d)"), OppositeIndex, OppositeAdj.X,
               OppositeAdj.Y);*/
        Neighbor->GetNeighbors().Chunks[OppositeIndex] = Chunk;
    }
    return Chunk;
}

UChunkManager::UChunkManager(
    UWorld* World,
    UWorldGenerator* Generator
): World(World), Generator(Generator)
{
}

AChunk* UChunkManager::GetChunk(FIntPoint Coordinate, bool Load)
{
    AChunk** Ptr = ChunkCache.Find(Coordinate);
    if (Ptr == nullptr)
    {
        if (Load)
        {
            return LoadChunk(Coordinate);
        }
        return nullptr;
    }
    return *Ptr;
}

void UChunkManager::SetBlock(const FIntVector& Vector, const FBlock& Block)
{
    FIntPoint ChunkPos = GlobalBlockToChunk(Vector);
    AChunk** Ptr = ChunkCache.Find(ChunkPos);
    if (Ptr == nullptr)
    {
        // TODO: Chunk not loaded, what to do?
        return;
    }
    AChunk* Chunk = *Ptr;
}

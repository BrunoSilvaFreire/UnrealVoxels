#include "Chunk.h"
#include <Voxels/Common/Masking.h>

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = true;
    StaticMesh = CreateDefaultSubobject<UProceduralMeshComponent>(FName("ChunkMesh"));
    StaticMesh->bSelectable = true;
    RootComponent = StaticMesh;
}

void AChunk::BeginPlay()
{
    Super::BeginPlay();
    memset(&Neighbors, 0, sizeof(FChunkNeighbor));
}

void AChunk::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsSet(flags, EChunkFlag::Populated) && (populationJob == nullptr || populationJob->IsDone()))
    {
        if (IsSet(flags, EChunkFlag::Dirty) && (generationJob == nullptr || generationJob->IsDone()))
        {
            if (generationJob != nullptr)
            {
                return;
            }

            //            uint8 id = 0;
            for (AChunk* Ptr : Neighbors.Chunks)
            {
                if (Ptr == nullptr)
                {
                    //                    UE_LOG(LogTemp, Warning, TEXT("Unable to generate (%d, %d) because %d is unintialized"), ChunkPosition.X, ChunkPosition.Y,id);
                    return;
                }
                //                id++;
            }
            // UE_LOG(LogTemp, Warning, TEXT("Generating"));
            generationJob = new FAsyncTask<FGenerationJob>(this);
            generationJob->StartSynchronousTask();
        }
    }
}

void AChunk::Populate(UWorldGenerator* Generator)
{
    UE_LOG(LogTemp, Warning, TEXT("Populating"));
    if (populationJob != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Job already scheduled"));
        return;
    }
    populationJob = new FAsyncTask<FPopulationJob>(this, Generator);
    populationJob->StartBackgroundTask();
}

void AChunk::SetChunkPosition(const FIntPoint& NewPosition)
{
    this->ChunkPosition = NewPosition;
}

UProceduralMeshComponent* AChunk::GetMeshComponent() const
{
    return StaticMesh;
}

FIntPoint AChunk::GetChunkPosition() const
{
    return ChunkPosition;
}

TBlockBuffer& AChunk::GetBlocks()
{
    return Blocks;
}

FChunkNeighbor& AChunk::GetNeighbors()
{
    return Neighbors;
}

TEnumAsByte<EChunkFlag>& AChunk::GetChunkFlags()
{
    return flags;
}

void AChunk::SetChunkFlags(const EChunkFlag& Flags)
{
    flags = Flags;
}

void AChunk::EnableChunkFlag(const EChunkFlag& Flags)
{
    flags = flags | Flags;
}

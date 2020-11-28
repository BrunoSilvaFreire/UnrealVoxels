#pragma once

#include <Voxels/World/Block.h>
#include <Voxels/World/Tasks/GenerationJob.h>
#include <Voxels/World/Tasks/PopulationJob.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Chunk.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EChunkFlag : uint8
{
    None = 0,
    Populated = 1 << 0,
    Dirty = 1 << 1
};

union FChunkNeighbor
{
    static uint8 IndexOf(FIntPoint Point)
    {
        int x = Point.X;
        int y = Point.Y;
        switch (y)
        {
        case 1:
            return 0;
        case -1:
            return 1;
        case 0:
            switch (x)
            {
            case -1:
                return 2;
            case 1:
                return 3;
            default: return -1;
            }

        default:
            return -1;
        }
    }

    struct
    {
        AChunk *North, *South, *East, *West;
    };

    AChunk* Chunks[4];
};

ENUM_CLASS_FLAGS(EChunkFlag);
UCLASS()
class VOXELS_API AChunk : public AActor
{
    GENERATED_BODY()
private:
    FAsyncTask<FGenerationJob>* generationJob;

    FAsyncTask<FPopulationJob>* populationJob;
    UPROPERTY(EditAnywhere)
    TEnumAsByte<EChunkFlag> flags;

    UPROPERTY(VisibleAnywhere)
    UProceduralMeshComponent* StaticMesh;
    FChunkNeighbor Neighbors;

    UPROPERTY(VisibleAnywhere)
    FIntPoint ChunkPosition;
    // UPROPERTY(VisibleAnywhere)
    TBlockBuffer Blocks;
public:
    AChunk();
protected:

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UProceduralMeshComponent* GetMeshComponent() const;

    void Populate(UWorldGenerator* Generator);

    void SetChunkPosition(const FIntPoint& ChunkPosition);

    FIntPoint GetChunkPosition() const;

    TBlockBuffer& GetBlocks();

    FChunkNeighbor& GetNeighbors();

    TEnumAsByte<EChunkFlag>& GetChunkFlags();

    void SetChunkFlags(const EChunkFlag& Flags);
    
    void EnableChunkFlag(const EChunkFlag& Flags);
};

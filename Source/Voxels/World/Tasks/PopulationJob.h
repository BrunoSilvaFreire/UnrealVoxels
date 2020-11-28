#pragma once

#include "CoreMinimal.h"

class UWorldGenerator;
class AChunk;

class VOXELS_API FPopulationJob final : public FNonAbandonableTask
{
    friend class FAsyncTask<FPopulationJob>;
private:
    AChunk* Chunk;
    UWorldGenerator * Generator;
public:

    explicit FPopulationJob(AChunk* Chunk, UWorldGenerator * Generator);

    ~FPopulationJob();
    void DoWork();

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FPopulationJob, STATGROUP_ThreadPoolAsyncTasks);
    }
};

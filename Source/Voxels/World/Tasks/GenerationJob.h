// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Voxels/Common/BlockFace.h>
#include "CoreMinimal.h"

class AChunk;

class VOXELS_API FGenerationJob : public FNonAbandonableTask
{
public:

    friend class FAsyncTask<FGenerationJob>;
private:
    AChunk* Chunk;
    TArray<FVector> Vertices;
    TArray<int32> Indices;
    TArray<FVector> Normals;
    void BuildFace(const FVector& Position, const FBlockFace& Face);
public:
    explicit FGenerationJob(AChunk* Chunk);
    ~FGenerationJob();
    void DoWork();

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FGenerationJob, STATGROUP_ThreadPoolAsyncTasks);
    }
};

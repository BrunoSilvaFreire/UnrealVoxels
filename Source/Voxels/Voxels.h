// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FVoxels
{
public:
    static constexpr uint8 ChunkSize = 32;
    static constexpr uint8 ChunkHeight = 64;
    static constexpr size_t ChunkArea = ChunkSize * ChunkSize;
    static constexpr size_t ChunkVolume = ChunkArea * ChunkHeight;
    static constexpr uint32 Scale = 32;
    static constexpr uint8 MapSize = 3;
};

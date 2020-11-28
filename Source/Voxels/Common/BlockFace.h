#pragma once
#include "Math/IntVector.h"
#include "Math/Vector.h"

struct FBlockFace
{
public:
    explicit FBlockFace(int32 X, int32 Y, int32 Z);
    explicit FBlockFace(FIntVector Direction);
    FIntVector Direction;
    FVector Up;
    FVector Right;
    static const FBlockFace Faces[6];
};

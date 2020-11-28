#include "BlockFace.h"
const FBlockFace FBlockFace::Faces[6] =
{
    FBlockFace(0, 1, 0),
    FBlockFace(0, -1, 0),
    FBlockFace(-1, 0, 0),
    FBlockFace(1, 0, 0),
    FBlockFace(0, 0, 1),
    FBlockFace(0, 0, -1)
};

FBlockFace::FBlockFace(int32 X, int32 Y, int32 Z) : FBlockFace(FIntVector(X, Y, Z))
{
}

FBlockFace::FBlockFace(FIntVector Direction): Direction(Direction)
{
    if (Direction.Z != 0)
    {
        // Vertical face
        Up = FVector(-1, 0, 0);
    }
    else
    {
        // Lateral face
        Up = FVector(0, 0, 1);
    }
    FVector UpF = static_cast<FVector>(Up);
    const FVector Normal = static_cast<FVector>(Direction);
    Right = FVector::CrossProduct(Normal, UpF);
}

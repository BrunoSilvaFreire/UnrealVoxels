#include "PopulationJob.h"
#include <Voxels/World/Chunk.h>
#include <Voxels/World/Generation/WorldGenerator.h>

FPopulationJob::FPopulationJob(AChunk* Chunk, UWorldGenerator* Generator): Chunk(Chunk), Generator(Generator)
{
}

FPopulationJob::~FPopulationJob()
{
}

void FPopulationJob::DoWork()
{
    TBlockBuffer& Blocks = Chunk->GetBlocks();
    Blocks.SetNum(FVoxels::ChunkVolume);
    if (Generator != nullptr)
    {
        Generator->Populate(Blocks, Chunk->GetChunkPosition());
        Chunk->SetChunkFlags(Chunk->GetChunkFlags() | EChunkFlag::Populated);
    }
}

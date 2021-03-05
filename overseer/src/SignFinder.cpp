#include "SignFinder.h"
#include "Blocks.h"
#include "CoordsHandler.h"

#include <iostream>
#include <fstream>
#include <chrono>

region_file_reader* SignFinder::m_RegionReader;
std::string SignFinder::m_WorldFile;

void SignFinder::SetRegionFile(std::string filePath)
{
	if (m_RegionReader != nullptr)
	{
		delete m_RegionReader;
	}

	m_RegionReader = new region_file_reader(filePath.c_str());
	m_RegionReader->read();
}

void SignFinder::SetWorldFile(std::string filePath)
{
	m_WorldFile = filePath;
}

void SignFinder::FindSigns()
{

	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	auto t1 = high_resolution_clock::now();

	int regionX = m_RegionReader->get_x_coord();
	int regionZ = m_RegionReader->get_z_coord();

	// iterate through every chunk in the region

	std::ofstream resultFile;
	resultFile.open(m_WorldFile + "/signs.txt", std::fstream::app);

	for (unsigned int z = 0; z < region_dim::CHUNK_WIDTH; z++)
	{
		for (unsigned int x = 0; x < region_dim::CHUNK_WIDTH; x++) {

			int chunkX = CoordsHandler::getGlobalChunkCoordsFromRegion(regionX) + x;
			int chunkZ = CoordsHandler::getGlobalChunkCoordsFromRegion(regionZ) + z;

			int chunkGlobalX = chunkX * 16;
			int chunkGlobalZ = chunkZ * 16;

			if (!m_RegionReader->is_filled(x, z))
				continue;

			unsigned int index = 0;

			// iterate through every block in the chunk
			for (unsigned int blockX = 0; blockX < 16; blockX++)
			{
				for (unsigned int blockZ = 0; blockZ < 16; blockZ++)
				{
					for (unsigned int blockY = 0; blockY < 256; blockY++)
					{
						auto block = m_RegionReader->get_block_at(x, z, blockX, blockY, blockZ);
						if (block == WALL_MOUNTED_SIGN || block == STANDING_SIGN)
						{
							int blockGlobalCoordsX = CoordsHandler::getGlobalBlockCoords(chunkGlobalX, blockX);
							int blockGlobalCoordsZ = CoordsHandler::getGlobalBlockCoords(chunkGlobalZ, blockZ);

							resultFile << "Sign at X: " << blockGlobalCoordsX << " " << "Y: " << blockY << " " << "Z: " << blockGlobalCoordsZ << "\n";
							resultFile.flush();

						}
						index++;
					}
				}
			}

		}
	}

	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);

	std::string regionName = "r." + std::to_string(regionX) + "." + std::to_string(regionZ) + ".mca";

	std::cout << "done iterating through region " << regionName << " operation took : " << ms_int.count() << " milliseconds." << std::endl;

}

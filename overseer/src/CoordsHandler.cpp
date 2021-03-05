#include "CoordsHandler.h"

#include <math.h>

int CoordsHandler::getGlobalChunkCoordsFromRegion(int regionCoord)
{
	if (regionCoord >= 0)
	{
		int result = 0;
		for (size_t i = 0; i < regionCoord; i++)
		{
			result += 32;
		}

		return result;
	}

	else
	{
		int result = 0;
		int region = abs(regionCoord);

		for (size_t i = 0; i < region; i++)
		{
			result += 32;
		}
		return -result;
	}

}

int CoordsHandler::getGlobalBlockCoords(int chunkCoords, int blockCoords)
{
	int result;

	result = chunkCoords + blockCoords;

	return result;
}

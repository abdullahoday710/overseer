#include "CoordsHandler.h"
#include "SignFinder.h"

#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char* argv[]) {
	if (argc != 2)
	{
		std::cerr << "Usage: overseer <path-to-world>" << std::endl;
		return 1;
	}


	std::filesystem::path worldPath = argv[1];
	if (!std::filesystem::exists(worldPath))
	{
		std::cerr << "Cannot open world file" << std::endl;
		return 1;
	}
	SignFinder::SetWorldFile(worldPath.string());

	std::fstream computedRegions;
	std::vector<std::string> computedRegionNames;

	computedRegions.open(worldPath.string() + "/computedRegions.overseer", std::fstream::in);
	std::string line;
	while (std::getline(computedRegions, line)) {
		computedRegionNames.push_back(line);
	}
	computedRegions.close();

	computedRegions.open(worldPath.string() + "/computedRegions.overseer", std::fstream::app);
	worldPath.append("region/");
	for (auto& p : std::filesystem::directory_iterator(worldPath))
	{
		
		if (std::find(computedRegionNames.begin(), computedRegionNames.end(), p.path().filename()) == computedRegionNames.end())
		{
			SignFinder::SetRegionFile(p.path().string());
			SignFinder::FindSigns();
			std::string filename = p.path().filename().string();

			computedRegions << filename << "\n";
			computedRegions.flush();
		}

	}

	return 0;
}
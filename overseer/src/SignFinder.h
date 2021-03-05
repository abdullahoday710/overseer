#pragma once
#include <region_file_reader.h>

#include <string>
class SignFinder
{
public:
	static void SetRegionFile(std::string filePath);
	static void SetWorldFile(std::string filePath);
	static void FindSigns();
private:
	static region_file_reader* m_RegionReader;
	static std::string m_WorldFile;
};


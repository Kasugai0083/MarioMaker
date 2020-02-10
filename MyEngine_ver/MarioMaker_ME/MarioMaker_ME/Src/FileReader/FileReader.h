#pragma once

#include "../Map/Map.h"
#include <string>


class FileReader
{
public:
	FileReader();
	~FileReader();

	void LoadCSV(std::string fileName_);
	void SaveCSV(std::string fileName_);
private:
	int tmp_map[MAP_H][MAP_W];
};


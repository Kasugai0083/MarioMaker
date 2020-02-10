#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "../FileReader/FileReader.h"

const int MAP_W = 40;
const int MAP_H = 23;

class Map
{
public:
	Map()
	{
		m_reader.LoadCSV("Csv/stage01.csv");
	};
	~Map();

private:
	int m_map[23][40];
	Drawer2D m_drawer2d;
	FileReader m_reader;
};


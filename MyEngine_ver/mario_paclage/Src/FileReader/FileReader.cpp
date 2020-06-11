#include "FileReader.h"
#include "../Data/Accessor.h"
#include <iostream>
#include <fstream> //for ifstream
#include <sstream> //for istringstream
#include <algorithm> //for replace

FileReader::FileReader()
{
	for (int i = 0; i < MAX_MAP_H; i++)
	{
		for (int j = 0; j < MAX_MAP_W; j++)
		{
			tmp_map[i][j] = 0;
		}
	}
}


FileReader::~FileReader()
{
}

void FileReader::LoadCSV(std::string fileName_) 
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }

	// ifstream => コンストラクタでファイル読み込み
	std::ifstream ifs(fileName_);

	// 読み込んだファイルを string で受け取り
	std::string str;

	// CSV 幅分の配列を確保
	int num[MAX_MAP_W];
	for (auto& i : num) { i = 255; }

	int j = 0;

	// 1 行読み込み
	// str に ifs から読み込んだ行を格納
	while (getline(ifs, str)) 
	{

		// 文頭から文末までのイテレーターを調査して
		// ',' を ' ' に変換する
		replace(str.begin(), str.end(), ',', ' ');

		// istringstream => 分割操作可能な文字列
		std::istringstream iss(str);

		// iss の要素を順番に取り出し
		for (int i = 0; i < MAX_MAP_W; i++)
		{
			iss >> num[i];
			if (num[i] != 255) { m_map_size.x = i + 1; }
		}
		for (int i = 0; i < MAX_MAP_W; i++)
		{
			tmp_map[j][i] = num[i];
		}
		j++;
	}
	m_map_size.y = j;

}

void FileReader::SaveCSV(std::string fileName_) 
{
	// 別ファイル出力用のコンテナクラス
	std::ofstream oss(fileName_);

	// 読み込んだファイルを string で受け取り
	std::string str;

	// 1 行読み込み
	// str に ifs から読み込んだ行を格納

	for (int i = 0; i < MAX_MAP_H; i++) 
	{
		for (int j = 0; j < MAX_MAP_W; j++) 
		{
			oss << tmp_map[i][j] << ",";
		}
		oss << "\n";
	}

	oss.close();

}


void FileReader::GetMapCSV(int* map_[MAX_MAP_H][MAX_MAP_W])
{
	for (int i = 0; i < MAX_MAP_H; i++)
	{
		for (int j = 0; j < MAX_MAP_W; j++)
		{
			*map_[i][j] = tmp_map[i][j];
		}
	}
}

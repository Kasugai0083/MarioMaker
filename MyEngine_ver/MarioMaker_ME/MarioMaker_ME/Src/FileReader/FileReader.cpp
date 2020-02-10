#include "FileReader.h"
#include <iostream>
#include <fstream> //for ifstream
#include <sstream> //for istringstream
#include <algorithm> //for replace

FileReader::FileReader()
{
	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
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
	// ifstream => コンストラクタでファイル読み込み
	std::ifstream ifs(fileName_);

	// 読み込んだファイルを string で受け取り
	std::string str;

	// CSV 幅分の配列を確保
	double num[MAP_W];

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
		for (int i = 0; i < 40; i++)
		{
			iss >> num[i];
		}
		for (int i = 0; i < 40; i++)
		{
			// 値の代入と "," の追加
			tmp_map[j][i] = num[i];
		}
		j++;
	}

}

void FileReader::SaveCSV(std::string fileName_) 
{
	// 別ファイル出力用のコンテナクラス
	std::ofstream oss(fileName_);

	// 読み込んだファイルを string で受け取り
	std::string str;

	// CSV 幅分の配列を確保
	double num[MAP_W];

	// 1 行読み込み
	// str に ifs から読み込んだ行を格納

	for (int i = 0; i < MAP_H; i++) 
	{
		for (int j = 0; j < MAP_W; j++) 
		{
			oss << tmp_map[i][j] << ",";
		}
		oss << "\n";
	}

	oss.close();

}


void FileReader::GetMapCSV(int* map_[MAP_H][MAP_W])
{
	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			*map_[i][j] = tmp_map[i][j];
		}
	}
}

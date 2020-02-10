#pragma once

#include "../Map/Map.h"
#include <string>


class FileReader
{
public:
	FileReader();
	~FileReader();
	/**
	* @brief csv ファイルの値を tmp_map に代入
	* @param fileName_ csv ファイルの名前を指定
	*/
	void LoadCSV(std::string fileName_);

	/**
	* @brief tmp_map の値を fileName_ に出力
	* @param fileName_ 出力する csv ファイルの名前を指定
	*/
	void SaveCSV(std::string fileName_);

	/**
	* @brief tmp_map の値を引数の配列に代入
	*/
	void GetMapCSV(int* map_[MAP_H][MAP_W]);
private:
	int tmp_map[MAP_H][MAP_W];	//!< @brief csv ファイルの値を一時的に保存
};


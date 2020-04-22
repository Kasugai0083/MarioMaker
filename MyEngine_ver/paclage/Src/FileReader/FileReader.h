#pragma once

#include "../Data/GameData.h"
#include "../Utility/Grid.h"
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
	void GetMapCSV(int* map_[MAX_MAP_H][MAX_MAP_W]);

	/**
	* @brief LoadCSV で読み込んだマップサイズを出力
	*/
	t_Grid GetMapSize() { return m_map_size; }
private:
	int tmp_map[MAX_MAP_H][MAX_MAP_W];	//!< @brief csv ファイルの値を一時的に保存
	t_Grid m_map_size;					//!< 読み込んだマップファイルのサイズ
};


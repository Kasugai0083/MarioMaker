#pragma once

#include "../Map/Map.h"
#include <string>


class FileReader
{
public:
	FileReader();
	~FileReader();
	/**
	* @brief csv �t�@�C���̒l�� tmp_map �ɑ��
	* @param fileName_ csv �t�@�C���̖��O���w��
	*/
	void LoadCSV(std::string fileName_);

	/**
	* @brief tmp_map �̒l�� fileName_ �ɏo��
	* @param fileName_ �o�͂��� csv �t�@�C���̖��O���w��
	*/
	void SaveCSV(std::string fileName_);

	/**
	* @brief tmp_map �̒l�������̔z��ɑ��
	*/
	void GetMapCSV(int* map_[MAP_H][MAP_W]);
private:
	int tmp_map[MAP_H][MAP_W];	//!< @brief csv �t�@�C���̒l���ꎞ�I�ɕۑ�
};


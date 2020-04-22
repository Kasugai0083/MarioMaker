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
	void GetMapCSV(int* map_[MAX_MAP_H][MAX_MAP_W]);

	/**
	* @brief LoadCSV �œǂݍ��񂾃}�b�v�T�C�Y���o��
	*/
	t_Grid GetMapSize() { return m_map_size; }
private:
	int tmp_map[MAX_MAP_H][MAX_MAP_W];	//!< @brief csv �t�@�C���̒l���ꎞ�I�ɕۑ�
	t_Grid m_map_size;					//!< �ǂݍ��񂾃}�b�v�t�@�C���̃T�C�Y
};


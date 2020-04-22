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

	// ifstream => �R���X�g���N�^�Ńt�@�C���ǂݍ���
	std::ifstream ifs(fileName_);

	// �ǂݍ��񂾃t�@�C���� string �Ŏ󂯎��
	std::string str;

	// CSV �����̔z����m��
	int num[MAX_MAP_W];
	for (auto& i : num) { i = 255; }

	int j = 0;

	// 1 �s�ǂݍ���
	// str �� ifs ����ǂݍ��񂾍s���i�[
	while (getline(ifs, str)) 
	{

		// �������當���܂ł̃C�e���[�^�[�𒲍�����
		// ',' �� ' ' �ɕϊ�����
		replace(str.begin(), str.end(), ',', ' ');

		// istringstream => ��������\�ȕ�����
		std::istringstream iss(str);

		// iss �̗v�f�����ԂɎ��o��
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
	// �ʃt�@�C���o�͗p�̃R���e�i�N���X
	std::ofstream oss(fileName_);

	// �ǂݍ��񂾃t�@�C���� string �Ŏ󂯎��
	std::string str;

	// 1 �s�ǂݍ���
	// str �� ifs ����ǂݍ��񂾍s���i�[

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

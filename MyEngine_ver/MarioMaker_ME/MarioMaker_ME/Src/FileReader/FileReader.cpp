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
	// ifstream => �R���X�g���N�^�Ńt�@�C���ǂݍ���
	std::ifstream ifs(fileName_);

	// �ǂݍ��񂾃t�@�C���� string �Ŏ󂯎��
	std::string str;

	// CSV �����̔z����m��
	double num[MAP_W];

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
		for (int i = 0; i < 40; i++)
		{
			iss >> num[i];
		}
		for (int i = 0; i < 40; i++)
		{
			// �l�̑���� "," �̒ǉ�
			tmp_map[j][i] = num[i];
		}
		j++;
	}

}

void FileReader::SaveCSV(std::string fileName_) 
{
	// �ʃt�@�C���o�͗p�̃R���e�i�N���X
	std::ofstream oss(fileName_);

	// �ǂݍ��񂾃t�@�C���� string �Ŏ󂯎��
	std::string str;

	// CSV �����̔z����m��
	double num[MAP_W];

	// 1 �s�ǂݍ���
	// str �� ifs ����ǂݍ��񂾍s���i�[

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

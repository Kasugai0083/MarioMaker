/**
* @file Texture.h
* @brief テクスチャの読み込み、解放など、テクスチャに関する関数、定数の宣言
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Scene/Scene.h"
#include "../Engine/Graphics.h"

void ReleaseCategoryTexture(std::string fileName_);

void AllReleaseTexture();

void LoadTexture(std::string fileName_);

Texture* GetTexture(std::string fileName_);

#endif

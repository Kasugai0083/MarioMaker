/**
* @file Texture.h
* @brief テクスチャの読み込み、解放など、テクスチャに関する関数、定数の宣言
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Scene/Scene.h"
#include "../Engine/Graphics.h"
#include "TitleSceneTex.h"
#include "GameSceneTex.h"
#include "ResultSceneTex.h"

#define MAX_TEXTURE_CATEGORY (SceneId::SceneIdMax)				//!< カテゴリー最大

/**
* @brief テクスチャデータ初期化関数@n
* ゲームで使用するテクスチャデータを保存出来るようにする
*/
void InitTexture();

/**
* @brief カテゴリー単位のテクスチャ解放関数@n
* 引数で指定されたカテゴリーのテクスチャを全て解放する
* @param[in] category_id 解放カテゴリー
*/
void ReleaseCategoryTexture(int category_id);

/**
* @brief テクスチャの全解放@n
* 読み込んでいるすべてのテクスチャを解放する@n
* ※この関数はEndEngineで使用されているので開発側で呼ぶ必要はない
*/
void AllReleaseTexture();

/**
* @brief テクスチャの読み込み@n
* 指定したされたパスのテクスチャを読み込み、カテゴリに登録する
* @return 読み込み結果(成功はtrue)
* @param[in] file_name 読み込むテクスチャ名(パス込み)
* @param[in] category_id 登録するカテゴリー
* @param[in] texture_id カテゴリー内のテクスチャID
*/
bool LoadTexture(const char* file_name, int category_id, int texture_id);
/**
* @brief テクスチャデータの取得@n
* 指定されたカテゴリのテクスチャデータを取得する
* @return テクスチャデータ(取得失敗時はnullptr)
* @param[in] 取得したいテクスチャのカテゴリ
* @param[in] 取得したいテクスチャのID
*/
Texture* GetTexture(int category_id, int texture_id);

#endif

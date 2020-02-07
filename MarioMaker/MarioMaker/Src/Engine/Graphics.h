/**
* @file Graphics.h
* @brief 描画に関する関数、定数の宣言
*/
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <Windows.h>
#include <d3d9.h>
#include "Lib/Lib.h"
#include "../Utility/Common.h"
#include "../Utility/Size.h"
#include "../Utility/Vec.h"
//#include "../Character/Enemy/Enemy.h"

/** @brief フォントカラー */
enum FontColor
{
	Black,			//!< 黒
	White,			//!< 白
	Red,			//!< 赤
	Yellow,
};

// @brief フォントサイズ */
enum FontSize
{
	Small,			//!< 小
	Regular,		//!< 中
	Large,			//!< 大
	FontSizeMax,	//!< サイズ最大数
};

#define SMALL_FONT_SIZE (16)	//!< フォントサイズ(小)
#define REGULAR_FONT_SIZE (24)	//!< フォントサイズ(中)
#define LARGE_FONT_SIZE (64)	//!< フォントサイズ(大)

/** @brief テクスチャデータやサイズを保持する構造体 */
struct Texture
{
	LPDIRECT3DTEXTURE9 TexutreData;	//!< テクスチャデータ
	float Width;						//!< 横幅
	float Height;						//!< 縦幅
};

struct AnimationTexture
{
	Texture* m_TextureData[10];

	int m_Speed;	// アニメションのスピード
	int m_Length;	// アニメーションの枚数
	int m_Counter;	// 現在何枚目かを数える変数
	float m_KillingCounter;
};


/**
* @brief Graphics機能初期化関数@n
* 描画関連を使用可能にするための初期化を行う@n
* ※Engine.cppのInitEngineで実行しているので@n
* 　使用者は自分たちで使う必要はない
* @return 初期化結果 (trueが成功)
*/
bool InitGraphics();

/**
* @brief Graphics機能終了関数@n
* 描画関連の処理の後始末を行う処理@n
* ※Engine.cppのEndEngineで実行しているので@n
* 　使用者は自分たちで使う必要はない
*/
void EndGraphics();

/**
* @brief 描画開始関数@n
* 描画開始を宣言し、バックバッファのクリアを行う
* @return 描画開始の成否 (成功はtrue)
*/
bool DrawStart();

/**
* @brief 描画終了関数@n
* 描画の終了を宣言し、バックバッファとフロントバッファを入れ替える@n
* ※この関数は必ずDrawStartの後に実行されるようにしてください。
*/
void DrawEnd();

/**
* @brief テクスチャ描画関数@n
* 指定された位置にテクスチャを描画する@n
* ※texture_dataはFile.hのGetTextureDataを使用してください。
* @param[in] x X軸描画座標
* @param[in] y Y軸描画座標
* @param[in] texture_data 描画で使用するテクスチャのデータ
*/
void DrawTexture(float x, float y, Texture* texture_data, float z_ = 0.f, float tu_ = 1.f, float tv_ = 1.f);
void DrawTexture(Vec2 pos_, Texture* texture_data);
void DrawTexture(float x, float y, Texture* texture_data, float width_, float height_);
void DrawTexture(float x, float y, Texture* texture_data, Size size_);
void CandleDraw(float x, float y, Texture* texture_data, Size size_, float hp_);
void CandleDraw(float x, float y, Texture* texture_data, Size size_, Size flame_, float hp_);


void DrawUVMappingTexture(float x, float y, Texture* texture_data, float texture_x, float texture_y, float rect_width, float rect_height);

/*
	アニメーションの描画用関数
*/
void DrawAnimation(float x_, float y_, AnimationTexture* animatinon_);
bool DrawBlood(float x_, float y_);

// in => true フェードイン
// in => false フェードアウト
void DrawFade(bool in_, D3DXCOLOR color_);

/**
* @brief テクスチャのUVスクロール描画関数@n
* 指定された情報でテクスチャをUVスクロールして描画する@n
* ※texture_dataはFile.hのGetTextureDataを使用してください。
* @param[in] x X軸描画座標
* @param[in] y Y軸描画座標
* @param[in] texture_data 描画で使用するテクスチャのデータ
* @param[in] tu テクスチャU座標
* @param[in] tv テクスチャV座標
*/
void DrawUVScrollTexture(float x, float y, Texture* texture_data, float tu, float tv);

/**
* @brief フォント描画関数@n
* 指定された位置にフォントを描画する@n
* @param[in] x X軸描画座標
* @param[in] y Y軸描画座標
* @param[in] text 描画するテキスト
* @param[in] size フォントサイズの種類
* @param[in] color フォントの色
*/
void DrawFont(float pos_x, float pos_y, const char* text, FontSize size, FontColor color);

/**
* @brief テクスチャ作成@n
* 指定された情報から読み込み、テクスチャを作成する@n
* ※開発側はFile.hのLoadTextureを使用してください。
* @return 作成結果(成功はtrue)
* @param[in] file_name 読み込むテクスチャの名前(パス込み)
* @param[out] texture_data 読み込まれたテクスチャを反映するデータ
*/
bool CreateTexture(const char* file_name, Texture* texture_data);

//統合画像から切り抜き用の関数
//全ての切り抜かれる画像の大きさが一定である必要がある
//tu,tv => 画像の割合
//tv,tv = (切り抜かれる画像サイズ / 統合画像のサイズ)
//spriteX,spriteY => 切り抜かれる画像サイズ
//spriteNumX,spriteNumY => 切り抜きたい画像の座標
void DrawIntegratedTexture(float x, float y, Texture* texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY);

//↓松本さんの関数↓//


//----------------------------
//頂点情報を生成する関数
void CreateVertex(
	Mastumoto::Vec2 pos,
	Mastumoto::Vec2 offset,
	Vertex vtx[4],
	D3DXCOLOR color = 0x00ffffff
);
//----------------------------
//頂点情報を生成する関数(中地構造体 対応ver)
void CreateVertex(
	Vec2 pos,
	Size offset,
	Vertex vtx[4],
	D3DXCOLOR color = 0x00ffffff
);

//--------------------------------
//テクスチャー付きの板ポリ描画関数
void DrawBox2D(
	const Lib::Texture& tex, Mastumoto::Vec2 pos);

//---------------------------------
//テクスチャー無し透過板ポリ描画
void DrawAlphaBox2D(
	const Lib::Texture& tex,
	Mastumoto::Vec2 pos,
	Mastumoto::Vec2 size,
	D3DXCOLOR col = 0x00ffffff
);
//---------------------------------
//テクスチャー無し透過板ポリ描画(中地構造体対応 ver)
void DrawAlphaBox2D(
	const Lib::Texture& tex,
	Vec2 pos,
	Size size,
	D3DXCOLOR col
);

//---------------------------------
//テクスチャー有り透過板ポリ描画
void DrawAlphaTex2D(
	const Lib::Texture& tex,
	Mastumoto::Vec2 pos,
	Mastumoto::Vec2 size,
	D3DXCOLOR col = 0x00ffffff
);

#endif

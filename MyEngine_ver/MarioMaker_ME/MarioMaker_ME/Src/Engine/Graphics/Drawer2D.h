#pragma once

#include "..//..//Utility/Vec2.h"
#include "..//..//Utility/Vec3.h"
#include "..//..//Utility/Size.h"
#include "DirectX.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>
#include <vector>


/**
* @brief
* 2Dポリゴン用の画像を保存・描画するクラス
*/

struct t_LineDesc;

class Drawer2D
{
public:

	/**
	* @brief テクスチャを貼り付けたポリゴンを描画する
	* @param v_ ポリゴンの頂点情報 と テクスチャの座標情報
	* @param fileName_ m_ptr_tex_list の要素
	*/
	void DrawTexture(t_VertexPos v_, std::string fileName_);


	/**
	* @brief m_ptr_tex_list にテクスチャ情報を入力\n
	* 読み込みに失敗した場合、エラーメッセージを返す
	* @param fileName_ 要素番号を指定
	*/
	void LoadTexture(std::string fileName_) {
		if (!CreateTexture(fileName_)) {
			std::string msg = " の読み込みに失敗";
			std::string pop_msg = fileName_ + msg;

			MessageBox(NULL, pop_msg.c_str(), NULL, MB_OK);
		}
	}

	/**
	* @brief テクスチャ情報を取得
	* @return テクスチャ情報のポインタを返す
	*/
	t_Texture* GetTexture(std::string fileName_) { return m_ptr_tex_list[fileName_]; }


	/**
	* @brief DrawTextA でテキストを表示\n
	* DrawTextA の都合上、Z軸は設定できない
	* @param pos_ テキストの座標
	* @param text_ テキストの内容
	*/
	void DrawFont(t_Vec2 pos_, std::string text_);

	/**
	* @brief 指定したテクスチャ領域を解放
	* @param 領域を指定
	*/
	void Release(std::string fileName_);
	/**
	* @brief 全てのテクスチャ領域を解放
	*/
	void AllRelease();

private:
	/**
	* @brief m_ptr_tex_list にテクスチャ情報を入力
	* @param fileName_ 要素番号を指定
	*/
	bool CreateTexture(std::string fileName_);

private:

	std::map<std::string, t_Texture*>m_ptr_tex_list; //!< @brief 画像情報を保管

};
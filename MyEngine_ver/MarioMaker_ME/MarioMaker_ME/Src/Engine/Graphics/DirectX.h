#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include "..//..//Utility/Size.h"
#include "../../Utility/Vec3.h"
#include "../../Utility/Vec2.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief 
* DirectXを初期化・管理するクラス
*/

/**
* Texture のデータとサイズを管理する構造体
*/
struct t_Texture {
	LPDIRECT3DTEXTURE9 texture_data;		//!< テクスチャデータ
	float width;						//!< 横幅
	float height;						//!< 縦幅
};

/**
* @brief ポリゴン描画に必要な頂点情報
* @param pos 座標
* @param tex_pos テクスチャ座標
*/
struct t_CustomVertex {

	float x, y, z;
	float rhw;
	float tu,tv;

	//D3DXVECTOR3 pos;
	//D3DXVECTOR2 tex_pos;

};

/**
* @brief ポリゴン描画に必要な頂点情報
* @param pos 座標
* @param tex_pos_start テクスチャ座標開始点
* @param tex_pos_end テクスチャ座標終了点
*/
struct t_VertexPos {

	Pos2 pos;
	Pos2 tex_pos_start, tex_pos_end;

};

/**
* @enum 各描画関数の描画次元をしていするのに使用
*/
enum class Dimendion {
	DIMENSION_2,
	DIMENSION_3,
};

/**
* @brief DirextXステータス構造体\n
* 受け渡しを簡略化するために構造体に纏める
*/
struct t_DxStatus 
{
	LPDIRECT3D9 d3d_interface;	//!< @brief DirectXインターフェース
	
	D3DPRESENT_PARAMETERS* d3d_present_param; //!< @brief DirectXの設定
	
	LPDIRECT3DDEVICE9 d3d_device; //!< @brief DirectXデバイス情報
};

class DxManager : public Singleton<DxManager>
{
public:

	/**
	* @brief DirectX を初期化
	* @param ウィンドウハンドル
	* @return 初期化に成功した場合 => true
	*/
	bool InitDirectX(HWND windowHandle_);

	/**
	* @brief DirectXでの描画情報を初期化\n
	* !画像バグ：ここは異常なし
	*/
	void StartDraw();

	/**
	* @brief DirectXでの描画情報を解放
	*/
	void EndDraw();

	/**
	* @brief DirectXのステータスを解放
	*/
	void Release();

	/**
	* @brief フォントのデバイスを作成
	* @param フォントの大きさを指定
	* @return デバイス作成に成功 => true
	*/
	bool CreateFontDevice(t_Size size_);

	/**
	* @return DirectX 構造体のアドレスを返す
	*/
	t_DxStatus* GetStatus() {
		if (!&m_dx_status) { return false; }
		return &m_dx_status;
	}

	/**
	* @return m_Font のアドレスを返す
	*/
	LPD3DXFONT& GetFont() {
		return m_font;
	}
protected:


protected:

	t_DxStatus m_dx_status;		//!< @brief DirectX の周辺情報を保管

	LPD3DXFONT m_font;			//!< @brief フォントの情報

private:
	friend Singleton<DxManager>;

	DxManager()
	{ 
		m_font = nullptr; 
	};
	virtual ~DxManager() {};

	DxManager(const DxManager&) = delete;
	DxManager& operator=(const DxManager&) = delete;
	DxManager(const DxManager&&) = delete;
	DxManager& operator=(const DxManager&&) = delete;
};



#endif
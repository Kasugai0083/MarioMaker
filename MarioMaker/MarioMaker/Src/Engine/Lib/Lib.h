
#include <d3d9.h>
#include<d3dx9.h>
#include <dsound.h>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <mmsystem.h>

#pragma once
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


#define NOMINMAX

//----------------------
//頂点情報構造体
struct Vertex
{
	D3DXVECTOR4 pos; //頂点座標
	DWORD		col; //色相
	D3DXVECTOR2 uv;  //UV座標

};

namespace Lib {

	extern HWND hWnd;
	extern LPDIRECT3D9 d3d;
	extern LPDIRECT3DDEVICE9 dev;

	//================================================
	//　デバイス設定関連
	//================================================

	/*
	使用方法：
	　例）
		Init(WINDOW_W,WINDOW_H,"サンプル");  // 初期化

		while(ProcessMessage()){			 // メッセージループ処理
			DrawBegin(0);					 // 描画処理開始
			DrawEnd();						 // 描画処理終了
		}
		AppEnd();							 // アプリ終了処理
	*/

	/*
	ウィンドウプロシージャ
		メッセージを受け取る
	*/
	LRESULT CALLBACK WinProc(
		HWND hwnd, UINT msg,
		WPARAM wp, LPARAM lp
	);

	/*
	ウィンドウ初期化処理
	引数:
		width :ウィンドウの幅
		height:ウィンドウの高さ
		title :ウィンドウ名
	*/
	void Init(
		int width, int height,
		const char* title
	);

	/*
	Windowsのデバイス設定
	引数：
	　h_instance:インスタンスハンドル
	　class_name：ウィンドウ名（※識別用）
	  wc　　　　：ウィンドウクラス構造体
	*/
	void SetWinDevice(
		HINSTANCE h_instance,
		const char* class_name,
		WNDCLASSEX *wc
	);

	/*
	ウィンドウの作成処理
	引数：
	　h_instance：ウィンドウハンドル
	　class_name：ウィンドウ名（※識別用）
	  const_char：ウィンドウ名
	*/
	void MakeWindow(
		HINSTANCE h_instance,
		const char* class_name,
		const char* title,
		int w, int h
	);

	/*
	DirectX９の初期化処理
	*/
	void InitD3D9();

	/*
	ウィンドウ終了処理
	　　DirectX９のリリース処理を行う
	*/
	void AppEnd();

	/*
	ウィンドウメッセージ処理
	*/
	bool ProcessMessage();

	/*
	描画開始処理
	引数：
	　Back_color：描画背景色
	*/
	void DrawBegin(DWORD back_color = 0xe0e0ff
	);

	/*
	描画終了処理
	*/
	void DrawEnd();

	void ErrMsg(std::string msg);

	//================================================
	// テクスチャ読み込み関連
	//================================================
	class Texture {

	public:

		/*
		使用方法：
		　<コンストラクタ>
		  例）
			・Texture tex("画像名");
			・Texture("画像名");
			・Texture tex = "画像名";

		　< LPDIRECTTEXTURE9をテクスチャクラスに代用する場合 >
		  例）
			LPDIRECTTEXTURE9 texture;
			Texutre tex("画像名");
			texture = tex;

		  < サイズ、名前を取得する場合 >
		  例）※リブ内での操作にしか有効ではないので注意
			 float size = tex.GetSize();
			 const char* name = tex.GetName();
		*/

		/*
		コンストラクタ
		*/
		Texture() :tex(nullptr), size(0.f, 0.f) {}
		Texture(const char* file_name);
		Texture(const Texture& t);

		Texture& operator=(const Texture& _tex);
		operator LPDIRECT3DTEXTURE9()const {
			return tex;
		};

		/*
		テクスチャサイズ取得関数
		*/
		const D3DXVECTOR2& GetSize() const {
			return size;
		};

		/*
		テクスチャ名取得関数
		*/
		const std::string& GetName() const {
			return name;
		};

		~Texture();
	private:

		LPDIRECT3DTEXTURE9 tex;
		D3DXVECTOR2 size;
		std::string name;

	};

}


#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"
#include "Window.h"
#include "../Utility/Size.h"
#include "../Utility/Vec.h"
#include "Lib/Lib.h"
#include "../Utility/Common.h"
#include "../Engine/Engine.h"

#define FVF (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct CustomVertex
{
	float X;			// X座標
	float Y;			// Y座標
	float Z;			// Z座標	
	float Rhw;			// 除算数

	float TextureX;		// テクスチャ座標X
	float TexrureY;		// テクスチャ座標Y
};

/*
	staticをグローバル変数に指定すると
	別のcppからのアクセスができなくなる

		メリット
			無駄なアクセスを減らせる

	staticとつける => さわるなを明示してる
*/

// グローバル変数
static LPDIRECT3D9 g_D3DInterface;						// DirectGraphicsインターフェース
static LPDIRECT3DDEVICE9 g_D3DDevice;					// DirectGraphicsデバイス
static LPD3DXFONT g_FontList[FontSize::FontSizeMax];	// フォントデバイスリスト

// インターフェースの作成
bool CreateGraphicsInterface();

// グラフィックデバイスの作成
bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param);

// ViewPortの設定
bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param);

// フォントデバイスの生成
bool CreateFontDevice();

bool InitGraphics()
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false)
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}

	if (SetUpViewPort(&present_param) == false)
	{
		return false;
	}

	if (CreateFontDevice() == false)
	{
		return false;
	}

	return true;
}

void EndGraphics()
{
	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		g_FontList[i]->Release();
	}
	g_D3DDevice->Release();
	g_D3DInterface->Release();
}

bool DrawStart()
{
	g_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	if (D3D_OK == g_D3DDevice->BeginScene())
	{
		return true;
	}

	return false;
}

void DrawEnd()
{
	g_D3DDevice->EndScene();
	g_D3DDevice->Present(NULL, NULL, NULL, NULL);
}


void DrawTexture(float x, float y, Texture* texture_data, float z_, float tu_, float tv_)
{
	CustomVertex v[4] =
	{
		{ x, y, z_, 1.0f, 0.0f, 0.0f }, //0
		{ x + texture_data->Width, y, z_, 1.0f, tu_, 0.0f }, //1
		{ x + texture_data->Width, y + texture_data->Height, z_, 1.0f, tu_, tv_ }, //2
		{ x, y + texture_data->Height, z_, 1.0f, 0.0f, tv_ }, //3
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);


	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

void DrawTexture(Vec2 pos_, Texture* texture_data)
{
	CustomVertex v[4] =
	{
		{ pos_.X, pos_.Y, 0.0f, 1.0f, 0.0f, 0.0f }, //0
		{ pos_.X + texture_data->Width, pos_.Y, 0.0f, 1.0f, 1.0f, 0.0f }, //1
		{ pos_.X + texture_data->Width, pos_.Y + texture_data->Height, 0.0f, 1.0f, 1.0f, 1.0f }, //2
		{ pos_.X, pos_.Y + texture_data->Height, 0.0f, 1.0f, 0.0f, 1.0f }, //3
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);


	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

void DrawTexture(float x, float y, Texture* texture_data, float width_, float height_)
{
	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + width_, y, 0.0f, 1.0f, 1.0f, 0.0f },
		{ x + width_, y + height_, 0.0f, 1.0f, 1.0f, 1.0f },
		{ x, y + height_, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}
void DrawTexture(float x, float y, Texture* texture_data, Size size_)
{

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + size_.Width, y, 0.0f, 1.0f, 1.0f, 0.0f },
		{ x + size_.Width, y + size_.Height, 0.0f, 1.0f, 1.0f, 1.0f },
		{ x, y + size_.Height, 0.0f, 1.0f, 0.0f, 1.0f },	
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}
void CandleDraw(float x, float y, Texture* texture_data, Size size_, float hp_)
{

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + size_.Width, y, 0.0f, 1.0f, 0.99f , 0.0f },
		{ x + size_.Width, y + size_.Height * hp_, 0.0f, 1.0f, 0.99f, 1.0f * hp_ },
		{ x, y + size_.Height * hp_, 0.0f, 1.0f, 0.0f, 1.0f * hp_ },
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}
void CandleDraw(float x, float y, Texture* texture_data, Size size_, Size flame_, float hp_)
{

	float meltpos = size_.Height / flame_.Height;

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + flame_.Width, y, 0.0f, 1.0f, 0.99f , 0.0f },
		{ x + flame_.Width, y + size_.Height * hp_, 0.0f, 1.0f, 0.99f, meltpos * hp_ },
		{ x, y + size_.Height * hp_, 0.0f, 1.0f, 0.0f, meltpos * hp_ },
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

void DrawUVMappingTexture(float x, float y, Texture* texture_data, float texture_x, float texture_y, float rect_width, float rect_height)
{
	float uv_left = texture_x / texture_data->Width;
	float uv_right = (texture_x + rect_width) / texture_data->Width;
	float uv_top = texture_y / texture_data->Height;
	float uv_bottom = (texture_y + rect_height) / texture_data->Height;

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, uv_left, uv_top },
		{ x + rect_width, y, 0.0f, 1.0f, uv_right, uv_top },
		{ x + rect_width, y + rect_height, 0.0f, 1.0f, uv_right, uv_bottom },
		{ x, y + rect_height, 0.0f, 1.0f, uv_left, uv_bottom },
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

//統合画像切り抜き用
void DrawIntegratedTexture(float x, float y, Texture* texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY)
{

	int tmpX = spriteNumX - 1;
	int tmpY = spriteNumY - 1;

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, tu*tmpX, tv*tmpY },
		{ x + spriteX, y, 0.0f, 1.0f, tu*spriteNumX, tv*tmpY },
		{ x + spriteX, y + spriteY, 0.0f, 1.0f, tu*spriteNumX, tv*spriteNumY },
		{ x, y + spriteY, 0.0f, 1.0f, tu*tmpX, tv*spriteNumY},
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

void DrawUVScrollTexture(float x, float y, Texture* texture_data, float tu, float tv)
{
	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, tu, tv },
		{ x + texture_data->Width, y, 0.0f, 1.0f, tu + 1.0f, tv },
		{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, tu + 1.0f, tv + 1.0f },
		{ x, y + texture_data->Height, 0.0f, 1.0f, tu, tv + 1.0f },
	};

	// 頂点構造の指定
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TexutreData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}


void DrawAnimation(float x_, float y_, AnimationTexture* animatinon_)
{
	static int Timer = 0;
	Timer++;
	
	animatinon_->m_KillingCounter += 0.1f;



	if (Timer > animatinon_->m_Speed) {

		++animatinon_->m_Counter;
		if (animatinon_->m_Counter > animatinon_->m_Length - 1) {

			animatinon_->m_Counter = 0;
		}
		Timer = 0;
	}

	DrawTexture(x_, y_, animatinon_->m_TextureData[animatinon_->m_Counter]);

}

void DrawFade(bool in_, D3DXCOLOR color_) {

	Lib::Texture polygon("hoge");

	Vec2 pos;
	pos.X = 0.f;
	pos.Y = 0.f;
	Size size;
	size.Width = 1920.f;
	size.Height = 1080.f;

	DrawAlphaBox2D(polygon, pos, size, color_);


}

bool DrawBlood(float x_, float y_) {
	Lib::Texture polygon("hoge");

	static float timer = 0.f;

	timer += 0.01f;

	Vec2 pos;
	pos.X = x_;
	pos.Y = y_;
	Size size;
	size.Width = 1920.f;
	size.Height = 1080.f;

	DrawAlphaBox2D(polygon, pos, size, D3DXCOLOR(0.5f, 0.f, 0.f, timer));

	if (timer >= 1.5f) {
		timer = 0.f;
		return true;
	}
	return false;
}

void DrawFont(float pos_x, float pos_y, const char* text, FontSize font_type, FontColor color)
{
	RECT rect =
	{
		(long)pos_x,
		(long)pos_y,
		(long)pos_x + 1500,
		(long)pos_y + 200,
	};

	int r, g, b;
	r = g = b = 255;

	if (color == FontColor::Black)
	{
		r = g = b = 0;
	}
	else if (color == FontColor::Red)
	{
		r = 255;
		g = b = 0;
	}
	else if (color == FontColor::Yellow)
	{
		r = 255;
		g = 215;
		b = 20;
	}

	g_FontList[font_type]->DrawTextA(
		NULL,
		text,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}

bool CreateTexture(const char* file_name, Texture* texture_data)
{
	Size size;
	D3DXIMAGE_INFO info;

	// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(g_D3DDevice,
		file_name,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_data->TexutreData)))
	{
		return false;
	}
	else
	{
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(texture_data->TexutreData->GetLevelDesc(0, &desc)))
		{
			texture_data->TexutreData->Release();
			return false;
		}
		texture_data->Width = desc.Width;
		texture_data->Height = desc.Height;
	}

	return true;
}

bool CreateGraphicsInterface()
{
	// インターフェース作成
	g_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_D3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}

	// 作成成功
	return true;
}


bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param)
{
	
	// バックバッファの数 => 1
	present_param->BackBufferCount = 1;
	//ディスプレイモード
	present_param->BackBufferFormat = D3DFMT_A8R8G8B8;

	//バックバッファからフロントバッファへ転送時のオプション
	present_param->Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

	// ウィンドウモード設定 => 定数で切り替え
	present_param->Windowed = true;
	//横の解像度
	present_param->BackBufferWidth = 1920;
	//縦の解像度
	present_param->BackBufferHeight = 1080;
	//フルスクリーンのリフレッシュレート
	present_param->FullScreen_RefreshRateInHz = 0;

	//マルチサンプルの数
	present_param->MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	//マルチサンプルの品質レベル
	present_param->MultiSampleQuality = 0;
	//深度ステンシルバッファがあるかどうか
	present_param->EnableAutoDepthStencil = TRUE;
	//ステンシルバッファのフォーマット
	present_param->AutoDepthStencilFormat = D3DFMT_D16;
	//スワップエフェクトの書き換えタイミング
	present_param->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDeviceの作成
	if (FAILED(g_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME.c_str(), nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param,
		&g_D3DDevice)))
	{
		return false;
	}

	return true;
}

bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = present_param->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = present_param->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(g_D3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

bool CreateFontDevice()
{
	int size_list[] =
	{
		SMALL_FONT_SIZE,
		REGULAR_FONT_SIZE,
		LARGE_FONT_SIZE
	};

	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		if (FAILED(D3DXCreateFont(g_D3DDevice,
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			NULL,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("ＭＳ　Ｐゴシック"),
			&g_FontList[i])))
		{
			return false;
		}
	}

	return true;
}

//----------------------------
//頂点情報を生成する関数
void CreateVertex(
	Mastumoto::Vec2 pos,
	Mastumoto::Vec2 offset,
	Vertex vtx[4],
	D3DXCOLOR color
) {
	D3DXCOLOR col;
	col.r = color.r;
	col.g = color.g;
	col.b = color.b;
	col.a = color.a;

	//今回は中心座標の描画にしてみたモス
	vtx[0] = { {(pos.x - offset.x),(pos.y - offset.y),0.f,1.f},col,{0.f,0.f} };
	vtx[1] = { {(pos.x + offset.x),(pos.y - offset.y),0.f,1.f},col,{1.f,0.f} };
	vtx[2] = { {(pos.x + offset.x),(pos.y + offset.y),0.f,1.f},col,{1.f,1.f} };
	vtx[3] = { {(pos.x - offset.x),(pos.y + offset.y),0.f,1.f},col,{0.f,1.f} };
}

//----------------------------
//頂点情報を生成する関数(中地構造体 対応ver)
void CreateVertex(
	Vec2 pos,
	Size offset,
	Vertex vtx[4],
	D3DXCOLOR color
) {
	D3DXCOLOR col;
	col.r = color.r;
	col.g = color.g;
	col.b = color.b;
	col.a = color.a;

	//今回は中心座標の描画にしてみたモス
	vtx[0] = { {(pos.X),(pos.Y),0.f,1.f},col,{0.f,0.f} };
	vtx[1] = { {(pos.X + offset.Width),(pos.Y),0.f,1.f},col,{1.f,0.f} };
	vtx[2] = { {(pos.X + offset.Width),(pos.Y + offset.Height),0.f,1.f},col,{1.f,1.f} };
	vtx[3] = { {(pos.X),(pos.Y + offset.Height),0.f,1.f},col,{0.f,1.f} };
}

//--------------------------------
//テクスチャー付きの板ポリ描画関数
void DrawBox2D(
	const Lib::Texture& tex, Mastumoto::Vec2 pos) {

	Mastumoto::Vec2 size = { (tex.GetSize().x / 2), (tex.GetSize().y / 2) };

	Vertex vtx[4];
	CreateVertex(pos, size, vtx);

	g_D3DDevice->SetTexture(0, tex);
	g_D3DDevice->SetFVF(FVF);
	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(Vertex));
}

//---------------------------------
//テクスチャー無し透過板ポリ描画
void DrawAlphaBox2D(
	const Lib::Texture & tex,
	Mastumoto::Vec2 pos,
	Mastumoto::Vec2 size,
	D3DXCOLOR col
) {

	Vertex vtx[4];
	CreateVertex(pos, size, vtx, col);

	g_D3DDevice->SetTexture(0, tex);
	g_D3DDevice->SetFVF(FVF);

	//出力したα値の反映方法を指定
	g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファ値を有効にするモス
	//Lib::dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ブレンドするテクスチャを指定（真上のtexモス）
	g_D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);//カラーの設定モス
	g_D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);//今回はテクスチャーの色をブレンドするモスよ

	//αブレンドの設定
	g_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);//アルファの設定モス
	g_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//これも、上と同じモス


	g_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//上で設定したアルファをブレンドします宣言モス
	g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//透過ポリゴンが２枚重なったたときの濃淡の設定モス

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(Vertex));
}
//---------------------------------
//テクスチャー無し透過板ポリ描画(中地構造体対応 ver)
void DrawAlphaBox2D(
	const Lib::Texture & tex,
	Vec2 pos,
	Size size,
	D3DXCOLOR col
) {

	Vertex vtx[4];
	CreateVertex(pos, size, vtx, col);

	g_D3DDevice->SetTexture(0, tex);
	g_D3DDevice->SetFVF(FVF);

	//出力したα値の反映方法を指定
	g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファ値を有効にするモス
	//Lib::dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ブレンドするテクスチャを指定（真上のtexモス）
	g_D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);//カラーの設定モス
	g_D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);//今回はテクスチャーの色をブレンドするモスよ

	//αブレンドの設定
	g_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);//アルファの設定モス
	g_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//これも、上と同じモス


	g_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//上で設定したアルファをブレンドします宣言モス
	g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//透過ポリゴンが２枚重なったたときの濃淡の設定モス
	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(Vertex));
}


//---------------------------------
//テクスチャー有り透過板ポリ描画
void DrawAlphaTex2D(
	const Lib::Texture & tex,
	Mastumoto::Vec2 pos,
	Mastumoto::Vec2 size,
	D3DXCOLOR col
) {

	Vertex vtx[4];
	CreateVertex(pos, size, vtx, col);

	g_D3DDevice->SetTexture(0, tex);
	g_D3DDevice->SetFVF(FVF);

	//出力したα値の反映方法を指定
	g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファ値を有効にするモス
	g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(Vertex));
}
#include "DirectX.h"
#include "..//Device.h"
#include <Windows.h>

bool DxManager::InitDirectX(HWND windowHandle_)
{
	// インターフェース作成 start
	// ここは大丈夫
	m_dx_status.d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_dx_status.d3d_interface)
	{
		// 作成失敗
		return false;
	}
	// インターフェース作成 end

	// グラフィックデバイスの作成 start
	m_dx_status.d3d_present_param = new D3DPRESENT_PARAMETERS;
	if (!m_dx_status.d3d_present_param)
	{
		return false;
	}
	ZeroMemory(m_dx_status.d3d_present_param, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	m_dx_status.d3d_present_param->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	m_dx_status.d3d_present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
	// ウィンドウモード設定 => 定数で切り替え
	m_dx_status.d3d_present_param->Windowed = true;
	//横の解像度
	m_dx_status.d3d_present_param->BackBufferWidth = WIN_W;
	//縦の解像度
	m_dx_status.d3d_present_param->BackBufferHeight = WIN_H;
	//フルスクリーンのリフレッシュレート
	m_dx_status.d3d_present_param->FullScreen_RefreshRateInHz = 0;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	m_dx_status.d3d_present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDeviceの作成
	if (FAILED(m_dx_status.d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle_,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_dx_status.d3d_present_param,
		&m_dx_status.d3d_device)))
	{
		return false;
	}
	// グラフィックデバイスの作成 end

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = m_dx_status.d3d_present_param->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = m_dx_status.d3d_present_param->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(m_dx_status.d3d_device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void DxManager::StartDraw() {
	m_dx_status.d3d_device->Clear(0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		0.0f,	// Zバッファの初期値
		0);		// ステンシルバッファの初期値

	m_dx_status.d3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_dx_status.d3d_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_dx_status.d3d_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_dx_status.d3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_dx_status.d3d_device->SetRenderState(D3DRS_LIGHTING, false);

	m_dx_status.d3d_device->BeginScene();
}

void DxManager::EndDraw() {

	m_dx_status.d3d_device->EndScene();

	m_dx_status.d3d_device->Present(NULL, NULL, NULL, NULL);
}

void DxManager::Release() {
	m_font->Release();
	m_dx_status.d3d_device->Release();
	m_dx_status.d3d_interface->Release();
	delete[] m_dx_status.d3d_present_param;
}

bool DxManager::CreateFontDevice(t_Size size_) {

	if (FAILED(D3DXCreateFont(m_dx_status.d3d_device,
		(int)size_.width,
		(int)size_.height,
		FW_REGULAR,
		NULL,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		TEXT("ＭＳ　Ｐゴシック"),
		&m_font)))
	{
		return false;
	}
	return true;
}
#include "Drawer2D.h"
#include "DirectX.h"
#include <vector>

void Drawer2D::DrawTexture(t_VertexPos v_, std::string fileName_)
{
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_ptr_tex_list[fileName_] ) {
		left_tu = v_.tex_pos_start.x / m_ptr_tex_list[fileName_]->width;
		right_tu =(v_.tex_pos_start.x + v_.tex_pos_end.x) / m_ptr_tex_list[fileName_]->width;
		top_tv = v_.tex_pos_start.y / m_ptr_tex_list[fileName_]->height;
		bottom_tv = (v_.tex_pos_start.y + v_.tex_pos_end.y) / m_ptr_tex_list[fileName_]->height;
	}

#if 0
	// デカイポリゴン問題
	// ここの値も正常
	t_CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos_start.x, v_.tex_pos_start.y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },															// 左上
		{ D3DXVECTOR3(v_.tex_pos_start.x, (v_.tex_pos_start.y + v_.tex_pos_end.y), 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },									// 左下
		{ D3DXVECTOR3((v_.tex_pos_start.x + v_.tex_pos_end.x), (v_.tex_pos_start.y + v_.tex_pos_end.y), 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },				// 右下
		{ D3DXVECTOR3((v_.tex_pos_start.x + v_.tex_pos_end.x), v_.tex_pos_start.y, 0.0f), D3DXVECTOR2(right_tu, top_tv)},										// 右上
	};
#else
	float harf_x = 0.f;
	float harf_y = 0.f;
	// 中心点の座標を指定する場合
	if (m_ptr_tex_list[fileName_]) {
		harf_x = m_ptr_tex_list[fileName_]->width / 2.0f;
		harf_y = m_ptr_tex_list[fileName_]->height / 2.0f;
	}

	// 三角形を描画
	t_CustomVertex v[] =
	{
		//{ D3DXVECTOR3(-harf_x, harf_y, 0.0f),  D3DXVECTOR2(left_tu, top_tv) },				// 左上
		//{ D3DXVECTOR3(harf_x, harf_y, 0.0f),   D3DXVECTOR2(right_tu, top_tv) },				// 右上
		//{ D3DXVECTOR3(harf_x, -harf_y, 0.0f),  D3DXVECTOR2(right_tu, bottom_tv) },			// 右下
		//{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },			// 左下

		//{ -harf_x, -harf_y, 0.0f, 1.f,left_tu, top_tv},			// 左上
		//{ -harf_x, harf_y, 0.0f, 1.f,left_tu, bottom_tv},			// 左下
		//{ harf_x, harf_y, 0.0f, 1.f,right_tu, bottom_tv},			// 右下
		//{ harf_x, -harf_y, 0.0f, 1.f,right_tu, top_tv},			// 右上

		{ v_.pos.x - harf_x, v_.pos.y - harf_y, 0.0f, 1.f,left_tu, top_tv},			// 左上
		{ v_.pos.x + harf_x, v_.pos.y - harf_y, 0.0f, 1.f,right_tu, top_tv},			// 右上
		{ v_.pos.x + harf_x, v_.pos.y + harf_y, 0.0f, 1.f,right_tu, bottom_tv},			// 右下
		{ v_.pos.x - harf_x, v_.pos.y + harf_y, 0.0f, 1.f,left_tu, bottom_tv},			// 左下
	};
#endif

	// 法線を設定していないの

	if (m_ptr_tex_list[fileName_]) {
		mgr->GetStatus()->d3d_device->SetTexture(0, m_ptr_tex_list[fileName_]->texture_data);
	}
	// ライティング
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	mgr->GetStatus()->d3d_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(t_CustomVertex));
}


bool Drawer2D::CreateTexture(std::string fileName_)
{
	t_Size size;
	D3DXIMAGE_INFO info;

	m_ptr_tex_list[fileName_] = new t_Texture;

	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return false; }

	// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
	D3DXGetImageInfoFromFileA(fileName_.c_str(), &info);

	if (FAILED(D3DXCreateTextureFromFileExA(mgr->GetStatus()->d3d_device,
		fileName_.c_str(),
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
		&m_ptr_tex_list[fileName_]->texture_data)))
	{
		return false;
	}
	else
	{
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(m_ptr_tex_list[fileName_]->texture_data->GetLevelDesc(0, &desc)))
		{
			m_ptr_tex_list[fileName_]->texture_data->Release();
			return false;
		}
		// デカいポリゴン問題
		// ここでは想定内の値が入っている
		m_ptr_tex_list[fileName_]->width = (float)desc.Width;
		m_ptr_tex_list[fileName_]->height = (float)desc.Height;
	}

	return true;
}

void Drawer2D::DrawFont(t_Vec2 pos_,std::string text_) {

	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	RECT rect =
	{
		(LONG)pos_.x,
		(LONG)pos_.y,
		(LONG)pos_.x + (LONG)1024.f,
		(LONG)pos_.y + (LONG)1024.f
	};

	LPD3DXFONT font = mgr->GetFont();

	font->DrawTextA(
		NULL,
		text_.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(255,255,255)
	);
}

void Drawer2D::Release(std::string fileName_) {

	m_ptr_tex_list[fileName_]->texture_data->Release();

	delete[] m_ptr_tex_list[fileName_];

	m_ptr_tex_list.clear();
}

void Drawer2D::AllRelease() {
	for (auto tex : m_ptr_tex_list) 
	{
		if (!tex.second) {
			delete tex.second;
			tex.second = nullptr;
		}
	}
}
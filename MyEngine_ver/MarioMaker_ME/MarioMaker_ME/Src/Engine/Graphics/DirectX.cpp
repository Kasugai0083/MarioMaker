#include "DirectX.h"
#include "..//Device.h"
#include <Windows.h>

bool DxManager::InitDirectX(HWND windowHandle_)
{
	// �C���^�[�t�F�[�X�쐬 start
	// �����͑��v
	m_dx_status.d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_dx_status.d3d_interface)
	{
		// �쐬���s
		return false;
	}
	// �C���^�[�t�F�[�X�쐬 end

	// �O���t�B�b�N�f�o�C�X�̍쐬 start
	m_dx_status.d3d_present_param = new D3DPRESENT_PARAMETERS;
	if (!m_dx_status.d3d_present_param)
	{
		return false;
	}
	ZeroMemory(m_dx_status.d3d_present_param, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	m_dx_status.d3d_present_param->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	m_dx_status.d3d_present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	m_dx_status.d3d_present_param->Windowed = true;
	//���̉𑜓x
	m_dx_status.d3d_present_param->BackBufferWidth = WIN_W;
	//�c�̉𑜓x
	m_dx_status.d3d_present_param->BackBufferHeight = WIN_H;
	//�t���X�N���[���̃��t���b�V�����[�g
	m_dx_status.d3d_present_param->FullScreen_RefreshRateInHz = 0;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	m_dx_status.d3d_present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(m_dx_status.d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle_,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_dx_status.d3d_present_param,
		&m_dx_status.d3d_device)))
	{
		return false;
	}
	// �O���t�B�b�N�f�o�C�X�̍쐬 end

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = m_dx_status.d3d_present_param->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = m_dx_status.d3d_present_param->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
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
		0.0f,	// Z�o�b�t�@�̏����l
		0);		// �X�e���V���o�b�t�@�̏����l

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
		TEXT("�l�r�@�o�S�V�b�N"),
		&m_font)))
	{
		return false;
	}
	return true;
}
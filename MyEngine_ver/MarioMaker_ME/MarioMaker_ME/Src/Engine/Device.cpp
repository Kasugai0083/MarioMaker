#include "Device.h"
#include "Graphics/DirectX.h"

namespace {

	/**
	* �}�E�X�֘A
	*/
	struct t_Point {
		POINT start = { 0,0 };//�N���b�N���ȊO�̍��W���擾
		POINT end = { 0,0 };  //�N���b�N���̍��W���擾
	}pt;

	bool is_drag = false; //�h���b�O����ϐ�
	bool is_click = false;//�_�u���N���b�N����ϐ�

	/**
	* �L�[�{�[�h�֘A
	*/
	const int INPUT_FRAME = 2;
	const int KEYNUM = 256;

	enum FLAME {

		KB_CUR = 0,
		KB_PRE,
	};
};

LRESULT CALLBACK WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wParam_, LPARAM lParam_)
{
	int timer = 0;

	switch (messageId_)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	/*
	�_�u���N���b�N���K�v�ɂȂ�����
	case WM_LBUTTONDBLCLK:

		if (!is_click) {
			is_click = 1;
		}
	*/

	// �}�E�X�{�^���N���b�N�J�n��
	case WM_LBUTTONDOWN:  // ��

		if (++timer >= 1) {
			is_click = true;
			pt.end.x = pt.start.x;
			pt.end.y = pt.start.y;
		}

		break;

	case WM_RBUTTONDOWN:  // �E
		MessageBox(NULL, "�E�N���b�N", NULL, MB_OK);
		break;
	case WM_MBUTTONDOWN:  // ��
		MessageBox(NULL, "�z�C�[���N���b�N", NULL, MB_OK);
		break;
		// �}�E�X�{�^���N���b�N�I����
	case WM_LBUTTONUP:
		is_click = false;

		pt.end = { 0,0 };
		break;

		// �}�E�X�J�[�\��(�\��or��\��)
	case WM_CREATE:
		ShowCursor(TRUE);
		break;

	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:

		// �X�V������W���擾
		pt.start.x = LOWORD(lParam_);
		pt.start.y = HIWORD(lParam_);
		break;

	case WM_SYSKEYDOWN: // �V�X�e���L�[�����J�n��
	case WM_SYSKEYUP:   // �V�X�e���L�[�I����
		MessageBox(NULL, "�V�X�e���L�[����", NULL, MB_OK);
		break;

	}

	return DefWindowProc(windowHandle_, messageId_, wParam_, lParam_);
}

namespace Device{
	bool MakeWindow(int x_, int y_, std::string name_) {

		DxManager* mgr = DxManager::GetInstance();


		HWND hWnd;
		WNDCLASSEX window_class = {
			sizeof(WNDCLASSEX),									// �\���̂̃T�C�Y
			CS_HREDRAW | CS_VREDRAW,							// �N���X�̃X�^�C��
			WindowProc,											// �E�B���h�E�v���V�[�W��
			0,													// �⏕������
			0,													// �⏕������
			GetModuleHandle(nullptr),							// ���̃v���O�����̃C���X�^���X�n���h��
			LoadIcon(nullptr, IDI_APPLICATION),					// �A�C�R���摜
			LoadCursor(NULL, IDC_ARROW),						// �J�[�\���摜
			NULL,												// �w�i�u���V(�w�i�F)
			NULL,												// ���j���[��
			name_.c_str(),										// �N���X��									
			NULL												// �������A�C�R��
		};
		
		// �\���̂̓o�^
		if (RegisterClassEx(&window_class) == 0)
		{
			return false;
		}

		// �E�B���h�E�쐬
		hWnd = CreateWindow(
			name_.c_str(),
			name_.c_str(),
			(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
			0,
			0,
			x_,
			y_,
			NULL,
			NULL,
			GetModuleHandle(nullptr),
			NULL);

		if (hWnd == NULL)
		{
			return false;
		}

		if (!mgr->InitDirectX(hWnd))
		{
			return false;
		}

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return true;
	}

	bool ProcessMessage() {
		MSG msg;

		//�@���b�Z�[�W���O�ł͖�����
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				return false;
			}
		}
		return true;
	}

	BYTE key[INPUT_FRAME][KEYNUM];

	bool KeyTest(const BYTE k) {
		return ((k & 0x80) != 0);
	}
	bool KeyUpdate() {
		memcpy(key[KB_PRE], key[KB_CUR], sizeof(*key));
		if (GetKeyboardState(key[KB_CUR])) { return true; }
		return false;
	}
	bool KeyOn(int nVirtKey_) {
		return KeyTest(key[KB_CUR][nVirtKey_]);
	}
	bool KeyPress(int nVirtKey_) {
		return KeyTest(key[KB_CUR][nVirtKey_]) && !KeyTest(key[1][nVirtKey_]);
	}
	bool KeyOff(int nVirtKey_) {
		return !KeyTest(key[KB_CUR][nVirtKey_]) && KeyTest(key[1][nVirtKey_]);
	}

	t_Vec2 GetMousePoint() {

		t_Vec2 vec(((float)pt.end.x),((float)pt.end.y));
		return vec;
	}

	t_Vec2 GetPointOnDrag() {
		t_Vec2 vec(((float)pt.start.x), ((float)pt.start.y));
		return vec;
	}
	
	const bool MouseOn() 
	{
		
		if (is_click)
		{
			return true;
		}
			
		return false;
		
	}
	
	const bool MousePress() 
	{
		
		if (is_click)
		{
			is_click = false;
			return true;
		}
			
		return false;
		
	}
}


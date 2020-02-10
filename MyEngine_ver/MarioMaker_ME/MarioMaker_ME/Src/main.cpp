
#include "Engine/Graphics/DirectX.h"
#include "Engine/Device.h"
#include "Engine/Graphics/Drawer2D.h"
#include "Scene/SceneController.h"
#include "Utility/Debug.h"
#include <string>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <cstdlib>
#include <crtdbg.h>



int APIENTRY WinMain(HINSTANCE ,HINSTANCE, LPSTR, INT)
{


	//DirectXシングルトン作成
	DxManager::CreateInstance();
	DxManager* dx_mgr = DxManager::GetInstance();

	// SceneController
	SceneController::CreateInstance();
	SceneController* scene_ctr = SceneController::GetInstance();


	if (!Device::MakeWindow(WIN_W,WIN_H,"MarioMaker_ME")) {
		MessageBox(NULL,"ウィンドウ作成失敗",NULL, MB_OK);
	}

	scene_ctr->Init(SceneID::TITLE);

	t_Size font_size{ 32.f,32.f };
	dx_mgr->CreateFontDevice(font_size);


	while (Device::ProcessMessage())
	{
		// ESCAPE キーで終了
		if(Device::KeyPress(VK_ESCAPE)){ PostQuitMessage(0); }

		Device::KeyUpdate();

		dx_mgr->StartDraw();

		// シーン制御
		scene_ctr->Update();
		scene_ctr->Draw();

		dx_mgr->EndDraw();

#if 1
		//メモリリークをチェック
		_CrtDumpMemoryLeaks();
#endif
	}

	scene_ctr->Release();

	dx_mgr->Release();

	SceneController::DestroyInstance();
	DxManager::DestroyInstance();

#if 0
	// メモリリークをチェック
	_CrtDumpMemoryLeaks();
#endif
}

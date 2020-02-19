#include "Engine/Engine.h"
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "Engine/Input.h"
#include "Engine/Graphics.h"
#include "Engine/Lib/Lib.h"
#include <Windows.h>
#include <cstdlib>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{

	{
		// ÉGÉìÉWÉìÇÃèâä˙âª
		if (InitEngine(1280, 720, "Mario") == false)
		{
			return 0;
		}

		SetCursorPos(640 / 2, 640 / 2);

		while (!GetKeyDown(KEY_INFO::ESC_KEY))
		{
			bool message_ret = false;
			MSG msg;



			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}
			}
			else
			{


				UpdateScene();

				_CrtDumpMemoryLeaks();
			}
		}
		EndEngine();
	}

	return 0;
}


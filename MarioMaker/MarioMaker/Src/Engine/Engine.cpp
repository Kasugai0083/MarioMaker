#include "Window.h"
#include "Graphics.h"
#include "Input.h"
#include "../Texture/Texture.h"
#include "Engine.h"

bool InitEngine(int width_, int height_, const char* titleName_)
{
	if (MakeWindow(width_, height_, titleName_) == false)
	{
		return false;
	}

	if (InitGraphics() == false)
	{
		return false;
	}

	if (InitInput() == false)
	{
		return false;
	}

	//InitTexture();

	return true;
}

void EndEngine()
{
	AllReleaseTexture();
	EndGraphics();
	ReleaseInput();
}

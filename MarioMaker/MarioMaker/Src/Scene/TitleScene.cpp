#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "TitleScene.h"
#include "../Engine/Calculation.h"
#include "Scene.h"
#include "../Engine/Lib/Lib.h"

// タイトルシーンの初期化
void InitTitleScene();
// タイトルシーンのメイン処理
void MainTitleScene();
// タイトルシーンの終了
SceneId FinishTitleScene();

SceneId UpdateTitleScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitTitleScene();
		break;
	case SceneStep::MainStep:
		MainTitleScene();
		break;
	case SceneStep::EndStep:
		return FinishTitleScene();
		break;
	}

	return SceneId::TitleScene;
}

void DrawTitleScene()
{
}



void InitTitleScene()
{

	ChangeSceneStep(SceneStep::MainStep);
}

void MainTitleScene()
{
	if (OnMouseDown(Left) == true) {
		ChangeSceneStep(SceneStep::EndStep);
	}
}

SceneId FinishTitleScene()
{	
	ReleaseCategoryTexture(TEXTURE_CATEGORY_TITLE);

	return SceneId::GameScene;

}


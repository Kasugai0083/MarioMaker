#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "ClearScene.h"
#include "../Engine/Calculation.h"

// ゲームオーバーシーンの初期化
void InitClearScene();
// ゲームオーバーシーンのメイン
void MainClearScene();
// ゲームオーバーシーンの終了
SceneId FinishClearScene();

int g_ClearCount = 0;

SceneId UpdateClearScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitClearScene();
		break;
	case SceneStep::MainStep:
		MainClearScene();
		break;
	case SceneStep::EndStep:
		return FinishClearScene();
		break;
	}

	return SceneId::ClearScene;
}

void DrawClearScene()
{
}



void InitClearScene()
{
	ChangeSceneStep(SceneStep::MainStep);

}

void MainClearScene()
{

	if (OnMouseDown(Left) == true) {
		ChangeSceneStep(SceneStep::EndStep);
	}
}

SceneId FinishClearScene()
{
	return SceneId::TitleScene;
}
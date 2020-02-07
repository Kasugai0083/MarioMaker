#include <stdio.h>
#include "../Scene/Scene.h"
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Engine/Calculation.h"
#include "GameScene.h"

// ゲーム本編シーンの初期化
void InitGameScene();
// ゲーム本編シーンのメイン処理
void MainGameScene();
// ゲーム本編シーンの終了
SceneId FinishGameScene();

//シーン遷移
SceneId UpdateGameScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitGameScene();
		break;
	case SceneStep::MainStep:
		MainGameScene();
		break;
	case SceneStep::EndStep:
		return FinishGameScene();
		break;
	}

	return SceneId::GameScene;
}


//シーンのメイン処理
void DrawGameScene()
{

}

void InitGameScene()
{

	ChangeSceneStep(SceneStep::MainStep);
}


void MainGameScene()
{
	if (OnMouseDown(Left) == true) {
		ChangeSceneStep(SceneStep::EndStep);
	}
}

SceneId FinishGameScene()
{

	return SceneId::ClearScene;

}


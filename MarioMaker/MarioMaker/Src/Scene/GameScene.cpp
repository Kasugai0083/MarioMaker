#include <stdio.h>
#include "../Scene/Scene.h"
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Engine/Calculation.h"
#include "GameScene.h"

// �Q�[���{�҃V�[���̏�����
void InitGameScene();
// �Q�[���{�҃V�[���̃��C������
void MainGameScene();
// �Q�[���{�҃V�[���̏I��
SceneId FinishGameScene();

//�V�[���J��
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


//�V�[���̃��C������
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


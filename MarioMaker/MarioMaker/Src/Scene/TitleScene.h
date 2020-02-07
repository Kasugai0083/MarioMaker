/**
* @file TitleScene.h
* @brief タイトルシーンの関数の宣言
*/
#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

/**
* @brief タイトルシーンの更新関数@n
* タイトルシーンの仕様が実行される
* @return 遷移先シーンID(基本はSceneId::TitleSceneが返る)
*/
SceneId UpdateTitleScene();

/**
* @brief タイトルシーンの描画関数@n
* タイトルシーンのオブジェクトを描画する関数
*/
void DrawTitleScene();

#endif

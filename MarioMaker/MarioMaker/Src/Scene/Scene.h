/**
* @file Scene.h
* @brief シーン全体を実行、描画する関数の宣言
*/
#ifndef SCENE_H_
#define SCENE_H_

/** @brief シーンID */
enum SceneId
{
	TitleScene,			//!< タイトルシーン
	GameScene,
	ClearScene,		//!< ゲームオーバーシーン
	SceneIdMax			//!< シーンID最大
};

/** @brief シーンステップ */
enum SceneStep
{
	InitStep,			//!< 初期化
	MainStep,			//!< メイン
	EndStep,			//!< 終了
};

/** @brief 現在実行中のシーンIDの取得関数 */
SceneId GetCurrentSceneId();

/** @brief 現在実行中のシーンステップの取得関数 */
SceneStep GetCurrentSceneStep();

/**
* @brief シーンステップ変更関数@n
* 引数で指定したステップに切り替える
* @param[in] next_step 次のステップ
*/
void ChangeSceneStep(SceneStep next_step);

/**
* @brief シーン実行関数@n
* シーン処理を実行する@n
* 内部で各シーンを動かすので使用者がUpdateTitleScene等を実行する必要はない
*/
void UpdateScene();

/**
* @brief シーン描画関数@n
* シーンのオブジェクトを描画する@n
* 内部で各シーン毎の描画を行うので使用者がDrawTitleScene等を実行する必要はない
*/
void DrawScene();

#endif

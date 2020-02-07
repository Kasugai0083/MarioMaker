#ifndef INPUT_H_
#define INPUT_H_

#include "../Utility/Vec.h"
#include <Windows.h>
#include <dinput.h>

/** @brief マウスボタンの種類 */
enum MouseButton
{
	Left,		//!< 左
	Right,		//!< 右
	Center,		//!< 真ん中
};

// @brife キーの種類
enum KEY_INFO
{
	ESC_KEY,
	SPACE_KEY,
	UP_KEY,
	DOWN_KEY,
	RIGHT_KEY,
	LEFT_KEY,
	A_KEY,
	W_KEY,
	S_KEY,
	D_KEY,
	RETURN_KEY,
	L_CONTROL,
	MAX_KEY_INFO,
};

/**
* @brief Input機能の初期化関数@n
* デバイスの入力取得に必要な初期化を行います
* InitEngineで実行されるので開発側が実行する必要はありません
* @return 初期化結果、成功の場合はtrue
* @param[in] hInstance インスタンスハンドル
* @param[in] hWindow ウィンドウハンドル
*/
bool InitInput();

/**
* @brief Input機能の終了関数@n
* Input機能を終了させます@n
* EndEngineで実行されるので開発側が実行する必要はありません
*/
void ReleaseInput();

/**
* @brief キーボードの入力情報の更新@n
* デバイスの入力情報の更新を行います@n
* 毎フレームに1度必ず実行する必要があります
*/
void KeyStateUpdate();

/**
* @brief キーが押されている状態の判定関数@n
* 指定したキーが押されているかを判定します
* @return 判定結果、押されているならtrue
* @param[in] key 判定したいキー
*/
bool GetKey(KEY_INFO key);

/**
* @brief 入力情報の更新@n
* デバイスの入力情報の更新を行う@n
* 毎フレームに１度必ず実行する必要がある
*/
void UpdateInput();

/**
* @brief キーが押された瞬間の判定関数@n
* 指定したキーが押された瞬間化を判定します
* @return 判定結果、押された瞬間ならtrue
* @param[in] key 判定したいキー
*/
bool GetKeyDown(KEY_INFO key);

/**
* @brief キーが離された瞬間の判定関数@n
* 指定したキーが離された瞬間化を判定します
* @return 判定結果、離されたならtrue
* @param[in] key 判定したいキー
*/
bool GetKeyUp(KEY_INFO key);

/**
* @brief クリックした瞬間判定関数@n
* 指定したマウスのボタンがクリックされた瞬間かどうかを判定する
* @return 判定結果(押された瞬間ならtrue)
* @param[in] button_type 判定したいボタンの種類
*/
bool OnMouseDown(MouseButton button_type);

/**
* @brief クリック中判定関数@n
* 指定したマウスのボタンがクリック中かどうかを判定する
* @return 判定結果(クリック中瞬間ならtrue)
* @param[in] button_type 判定したいボタンの種類
*/
bool OnMousePush(MouseButton button_type);

/**
* @brief クリック終了判定関数@n
* 指定したマウスのボタンがクリックを終了した瞬間かどうかを判定する
* @return 判定結果(クリックをやめた瞬間ならtrue)
* @param[in] button_type 判定したいボタンの種類
*/
bool OnMouseUp(MouseButton button_type);

/** @brief マウスの座標取得関数 */
Vec2 GetMousePos();

#endif
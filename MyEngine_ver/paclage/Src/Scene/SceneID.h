#pragma once
/**
* @brief 
* シーンを識別する列挙子
*/

/**
* シーン識別子
*/
enum class SceneID {
	TITLE,
	GAME,
	RESULT,
	UNKNOWN,
};

/**
* @enum シーン状態識別子
*/
enum class SceneState {
	INIT,
	UPDATE,
	END,
	UNKNOWN,
};
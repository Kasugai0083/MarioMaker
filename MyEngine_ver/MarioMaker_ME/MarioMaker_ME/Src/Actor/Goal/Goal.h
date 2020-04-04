#pragma once

#include "../ActorBase.h"

enum class GoalType
{
	INDIVIDUAL,
	UP,
	MIDDLE,
	DOWN,
	ETC
};

class Goal : public ActorBase
{
public:
	Goal(Pos2 pos_, std::string fileName_)
	{
		Init(pos_, fileName_);		//!< 初期化
	};
	Goal(Pos2 pos_, GoalType type_, std::map<std::string, std::string*> nameList_)
	{
		Accessor* acs = Accessor::GetInstance();
		if (!acs) { return; };

		m_type = type_;
		m_name_list = nameList_;
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();

		Init(pos_);
	};
	~Goal()override;

	void Init(Pos2 pos_)override;		//!< 初期化
	void Init(Pos2 pos_, std::string fileNam1_)override;		//!< 初期化
	void Update()override;										//!< 更新
	void Draw()override;	//!< 描画
	void Draw(std::string fileName_, Camera* camera_)override;	//!< 描画
	void Release()override;										//!< 解放
private:
	GoalType m_type;
};


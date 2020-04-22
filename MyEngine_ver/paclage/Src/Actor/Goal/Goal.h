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

	void Init(Pos2 pos_)override;		//!< ‰Šú‰»
	void Update()override;										//!< XV
	void Draw()override;	//!< •`‰æ
	void Release()override;										//!< ‰ð•ú
private:
	GoalType m_type;
};


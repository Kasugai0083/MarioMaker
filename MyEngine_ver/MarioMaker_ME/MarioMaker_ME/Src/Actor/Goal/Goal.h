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
		Init(pos_, fileName_);		//!< ‰Šú‰»
	};
	Goal(Pos2 pos_, int id_,std::vector<std::string> name_list_)
	{
		Init(pos_);
		for (auto i : name_list_) { m_drawer2d.LoadTexture(i); }
	};
	~Goal()override;

	void Init(Pos2 pos_)override;		//!< ‰Šú‰»
	void Init(Pos2 pos_, std::string fileNam1_)override;		//!< ‰Šú‰»
	void Update()override;										//!< XV
	void Draw(std::string fileName_, Camera* camera_)override;	//!< •`‰æ
	void Release()override;										//!< ‰ð•ú
private:
};


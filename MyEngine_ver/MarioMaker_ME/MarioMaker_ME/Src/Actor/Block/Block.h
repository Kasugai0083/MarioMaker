#pragma once

#include "..//ActorBase.h"

class Block : public ActorBase
{
public:
	Block(Pos2 pos_, std::string fileName_) 
	{
		Init(pos_,fileName_);
	};
	~Block() override;

	void Init(Pos2 pos_, std::string fileName_)override;
	void Draw(std::string fileName_)override;
	void Update()override;
	void Release()override;

private:

	float m_reaction; //!< @brief ”½ì—p‚Ì—Í

};


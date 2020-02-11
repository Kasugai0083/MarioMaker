#pragma once

#include "..//..//Engine/Graphics/Drawer2D.h"

class Block
{
public:
	Block(Pos2 pos_, std::string fileName_) 
	{
		Init(pos_,fileName_);
	};
	~Block();

	void Init(Pos2 pos_, std::string fileName_);
	void Draw(std::string fileName_);
	void Update();
	void Release();

private:

	Pos2 m_pos;

	float m_reaction; //!< @brief ”½ì—p‚Ì—Í

	Drawer2D m_drawer2d;

};


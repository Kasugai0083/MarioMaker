#pragma once

#include "../../ActorBase.h"

class Player :
	public ActorBase
{
public:
	Player(Pos2 pos_, std::string fileName_) { Init(pos_, fileName_); };
	~Player() override;

	void Init(Pos2 pos_, std::string fileName_) override;
	
	void Update() override;

	void Draw(std::string fileName_) override;

	void Release() override;
private:

};


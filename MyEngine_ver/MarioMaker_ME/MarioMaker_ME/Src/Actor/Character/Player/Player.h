#pragma once

#include "../CharacterBase.h"

class Player :
	public CharacterBase
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


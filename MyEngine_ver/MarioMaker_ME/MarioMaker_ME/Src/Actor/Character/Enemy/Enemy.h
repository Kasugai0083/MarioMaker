#pragma once

#include "../CharacterBase.h"

class Enemy :
	public CharacterBase
{
public:
	Enemy(Pos2 pos_, std::string fileName_) { Init(pos_, fileName_); };
	~Enemy() override;

	void Init(Pos2 pos_, std::string fileName_) override;

	void Update() override;

	void Draw(std::string fileName_) override;

	void Release() override;
};


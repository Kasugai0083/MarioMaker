#pragma once

#include "../ActorBase.h"

class Goal : public ActorBase
{
public:
	Goal(Pos2 pos_, std::string fileName_)
	{
		Init(pos_, fileName_);		//!< 初期化
	};
	//Goal(Pos2 pos_, std::string fileName1_, std::string fileName2_, std::string fileName3_)
	//{
	//	Init(pos_);
	//	m_drawer2d.LoadTexture(fileName1_);
	//	m_drawer2d.LoadTexture(fileName2_);
	//	m_drawer2d.LoadTexture(fileName3_);
	//};
	~Goal()override;

	void Init(Pos2 pos_)override;		//!< 初期化
	void Init(Pos2 pos_, std::string fileNam1_)override;		//!< 初期化
	void Update()override;										//!< 更新
	void Draw(std::string fileName_, Camera* camera_)override;	//!< 描画
	void Release()override;										//!< 解放
private:

};


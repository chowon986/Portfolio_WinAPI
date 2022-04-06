#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

class Monster : public CharacterBase
{
public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	int HP_;
	float4 Pos_;

private:
	int Speed_;
	GameEngineRenderer* WaddlediRenderer_;

private:
	void Walk();
	void Jump();
	bool IsDie();
	void attack();
	void GetPos(float4 _Pos);
	void Start();
	void Update();
	// 지속적으로 게임이 실행될때 호출된다.
	void Render();

public:

};


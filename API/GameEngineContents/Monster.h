#pragma once
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class Monster
{
public: 
	int HP_;
	float4 Pos_;

public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:

private:
	void Walk();
	void Jump();
	bool IsDie();
	void attack();
	void GetPos(float4 _Pos);
};


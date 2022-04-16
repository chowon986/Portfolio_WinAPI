#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

enum class MonsterState
{
	WALK,
	FLY,
	ATTACK,
	DIE,
};

class GameEngineImage;
class GameEngineLevel;
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
	float4 Pos_;

private:
	int Speed_;
	GameEngineRenderer* WaddlediRenderer_;
	MonsterState MonsterState_;
	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;

private:
	void Walk();
	void Jump();
	bool IsDie();
	void attack();
	void GetPos(float4 _Pos);
	void Start();
	void Update();
	void SetState(MonsterState _PrevState);
	void Render();

public:

};


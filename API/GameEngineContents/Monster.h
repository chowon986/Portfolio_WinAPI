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

enum class MonsterClass
{
	NONE,
	DEFAULT,
	SPARK,
	BEAM,
	SWORD,
	FIRE,
	ICE,
	ANIMAL,
	BOSS
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
	float4 Dir_;

private:
	int Speed_;
	GameEngineRenderer* WaddlediRenderer_;
	MonsterState MonsterState_;
	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;
	MonsterClass MonsterClass_;


public:
	GameEngineCollision* RightDirCol_;
	GameEngineCollision* LeftDirCol_;
	void SetMonsterClass(MonsterClass _MonsterClass)
	{
		MonsterClass_ = _MonsterClass;
	}

	MonsterClass GetMonsterClass()
	{
		return MonsterClass_;
	}
	void SetDir(float4 _Dir) { Dir_ = _Dir; }

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
	void Die();

public:

};


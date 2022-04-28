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
class Player;
class GameEngineRenderer;
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
	virtual bool IsDie();
	virtual void Die();
	virtual void UpdateMove();
	virtual bool CanWalk();
	virtual void Walk();
	void Start();
	void Update();
	void Render();
	

protected:
	float4 Pos_;
	float4 Dir_;
	float Speed_;
	float Time_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* IceEndCol_;
	MonsterState MonsterState_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* EffectRenderer_;
	GameEngineCollision* IceCol_;
	GameEngineCollision* RightDirCol_;
	GameEngineCollision* LeftDirCol_;
	GameEngineLevel* Level_;
	MonsterClass MonsterClass_;
	Player* Player_;


public:
	void SetMonsterClass(MonsterClass _MonsterClass)
	{
		MonsterClass_ = _MonsterClass;
	}

	MonsterClass GetMonsterClass()
	{
		return MonsterClass_;
	}
	void SetDir(float4 _Dir) { Dir_ = _Dir; }
	GameEngineRenderer* GetRenderer() { return Renderer_; }

private:
	void Jump();
	void attack();
	void GetPos(float4 _Pos);
	void SetState(MonsterState _PrevState);

public:
	void SetPlayer(Player* _Player) { Player_ = _Player; }
	Player* GetPlayer() { return Player_; }
};


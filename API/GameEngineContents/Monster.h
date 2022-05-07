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
	SWORD,
	FIRE,
	ICE,
	ANIMAL,
	BOSS
};

class DieEffect;
class GameEngineImage;
class GameEngineLevel;
class Player;
class GameEngineRenderer;
class FireAttackEffect;
class SparkAttackEffect;
class MonBotUI;
class Monster : public CharacterBase
{
public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	virtual void SetHP(int _HP) override;
	virtual int GetMaxHP() { return 2; }

protected:
	virtual bool IsDie();
	virtual void Die();
	virtual void UpdateMove();
	virtual bool CanWalk();
	virtual void Walk();	
	void Start();
	void Render();
	

protected:
	MonBotUI* MonStatus_;
	float4 Pos_;
	float4 Dir_;
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
	FireAttackEffect* Fire_;
	SparkAttackEffect* Spark_;


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

	void SetDieEffect(DieEffect* _DieEffect)
	{
		DieEffect_ = _DieEffect;
	}

private:
	void Jump();
	void attack();
	void GetPos(float4 _Pos);
	void SetState(MonsterState _PrevState);
	DieEffect* DieEffect_;

public:
	void SetPlayer(Player* _Player) { Player_ = _Player; }
	Player* GetPlayer() { return Player_; }	
	void SetFireEffect(FireAttackEffect* _Fire) { Fire_ = _Fire; }
	FireAttackEffect* GetFireEffect() { return Fire_; }
	void SetSparkEffect(SparkAttackEffect* _Spark) { Spark_ = _Spark; }
	SparkAttackEffect* GetSparkEffect() { return Spark_; }

};


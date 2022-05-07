#pragma once
#include "Monster.h"
#include <string>

enum class DededeState
{
	IDLE,
	WALK,
	JUMP,
	JUMPDOWN,
	ATTACK,
	YELL,
	FLYUP,
	FLY,
	FLYDOWN,
	FLYDOWNATTACK,
	DIE
};

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class Player;
class Dedede : public Monster
{
public:
	Dedede();
	~Dedede();

	Dedede(const Dedede& _Other) = delete;
	Dedede(Dedede&& _Other) noexcept = delete;
	Dedede& operator=(const Dedede& _Other) = delete;
	Dedede& operator=(Dedede&& _Other) noexcept = delete;

	int GetMaxHP() override { return 13; }

public:
	void Start() override;
	void Render() override;
	void DelayUpdate() override;
	void UpdateMove() override;
	void StateUpdate();
	void SetState(DededeState _DededeState);
	DededeState GetState() { return DededeState_; }
	void UpdateIdle();
	void UpdateWalk();
	void UpdateJump();
	void UpdateJumpDown();
	void UpdateAttack();
	void UpdateYell();
	void UpdateFlyUp();
	void UpdateFly();
	void UpdateFlyDown();
	void UpdateFlyDownAttack();
	void UpdateDie();

protected:

private:
	float4 PrevPos_;
	float4 PlayerPos_;
	float4 PlayerFlyPos_;
	float Time_;
	float AttTime_;
	float FlyUpTime_;
	float FlyAttackTime_;
	float JumpTime_;
	DededeState DededeState_;
	std::string Direction_;


private:
};
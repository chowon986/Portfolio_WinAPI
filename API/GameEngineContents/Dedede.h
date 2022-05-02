#pragma once
#include "Monster.h"
#include <string>

enum class DededeState
{
	IDLE,
	WALK,
	JUMP,
	ATTACK,
	YELL,
	FLY,
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

public:
	void Start() override;
	void Render() override;
	void Update() override;
	void UpdateMove() override;
	void StateUpdate();
	void SetState(DededeState _DededeState);
	DededeState GetState() { return DededeState_; }
	void UpdateIdle();
	void UpdateWalk();
	void UpdateJump();
	void UpdateAttack();
	void UpdateYell();
	void UpdateFly();
	void UpdateDie();

protected:

private:
	float4 PrevPos_;
	float4 PlayerPos_;
	float Time_;
	float AttTime_;
	DededeState DededeState_;
	std::string Direction_;


private:
};
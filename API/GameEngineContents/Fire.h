#pragma once
#include "Monster.h"

class GameEngineRenderer;
class GameEngineCollision;
class Fire : public Monster
{
public:
	Fire();
	~Fire();

	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void DelayUpdate() override;
	bool CanWalk() override;
	void Walk() override;
	void UpdateAttack();

protected:

private:
	GameEngineRenderer* AttackRenderer_;
	GameEngineCollision* AttackCol_;
	GameEngineCollision* AttackRangeCol_;
	bool CanMove_;
	float AttackTime_;
};
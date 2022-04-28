#pragma once
#include "Monster.h"

class GameEngineCollision;
class GameEngineRenderer;
class Sparky : public Monster
{
public:
	Sparky();
	~Sparky();

	Sparky(const Sparky& _Other) = delete;
	Sparky(Sparky&& _Other) noexcept = delete;
	Sparky& operator=(const Sparky& _Other) = delete;
	Sparky& operator=(Sparky&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
	bool CanWalk() override;
	void Walk() override;
	void UpdateAttack();

private:
	GameEngineRenderer* AttackRenderer_;
	GameEngineCollision* AttackCol_;
	GameEngineCollision* AttackRangeCol_;
	bool CanMove_;
	float AttackTime_;
};
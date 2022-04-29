#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Sword : public Monster
{
public:
	Sword();
	~Sword();

	Sword(const Sword& _Other) = delete;
	Sword(Sword&& _Other) noexcept = delete;
	Sword& operator=(const Sword& _Other) = delete;
	Sword& operator=(Sword&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
	bool CanWalk() override;
	void Walk() override;
	void UpdateAttack();

protected:

private:
	GameEngineCollision* AttackCol_;
	GameEngineCollision* AttackRangeCol_;
	bool CanMove_;
	float AttackTime_;
};
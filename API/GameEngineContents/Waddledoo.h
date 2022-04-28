#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class Waddledoo : public Monster
{
public:
	Waddledoo();
	~Waddledoo();

	Waddledoo(const Waddledoo& _Other) = delete;
	Waddledoo(Waddledoo&& _Other) noexcept = delete;
	Waddledoo& operator=(const Waddledoo& _Other) = delete;
	Waddledoo& operator=(Waddledoo&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
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

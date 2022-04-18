#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Player;
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
	bool IsDie();
	void Die();
	void UpdateMove();
	void UpdateAttack();

protected:

private:
	Player* Player_;
	GameEngineImage* ColMapImage_;
	GameEngineCollision* WaddledooCol_;
	GameEngineCollision* DirectionCol_;
	GameEngineCollision* AttackRangeCol_;
	GameEngineCollision* AttackCol_;

	GameEngineRenderer* WaddledooRenderer_;
	GameEngineRenderer* AttackRenderer_;
	GameEngineLevel* Level_;
	float4 Dir_;
};

#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class Player;
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
protected:

private:
	void UpdateMove();
	void UpdateAttack();
	bool IsDie();
	void Die();

private:
	GameEngineImage* ColMapImage_;
	GameEngineCollision* SparkyCol_;
	GameEngineCollision* DirectionCol_;
	GameEngineCollision* AttackRangeCol_;
	GameEngineCollision* AttackCol_;
	Player* Player_;

	GameEngineRenderer* SparkyRenderer_;
	GameEngineRenderer* AttackRenderer_;
	GameEngineLevel* Level_;
	float4 Dir_;
};
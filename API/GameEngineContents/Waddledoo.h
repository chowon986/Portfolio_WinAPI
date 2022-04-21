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
	float4 Dir_;
	Player* Player_;
	GameEngineLevel* Level_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* AttackRenderer_;
	GameEngineCollision* AttackCol_;
	GameEngineCollision* Collision_;
	GameEngineCollision* RightDirCol_;
	GameEngineCollision* LeftDirCol_;
	GameEngineCollision* AttackRangeCol_;
};

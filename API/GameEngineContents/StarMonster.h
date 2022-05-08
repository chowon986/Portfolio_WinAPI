#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class StarMonster : public Monster
{
private:

public:
	StarMonster();
	~StarMonster();

	StarMonster(const StarMonster& _Other) = delete;
	StarMonster(StarMonster&& _Other) noexcept = delete;
	StarMonster& operator=(const StarMonster& _Other) = delete;
	StarMonster& operator=(StarMonster&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void DelayUpdate() override;

private:
	GameEngineCollision* Collision_;
};
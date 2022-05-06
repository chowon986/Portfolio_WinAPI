#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class BigBomb : public Monster
{
public:
	BigBomb();
	~BigBomb();

	BigBomb(const BigBomb& _Other) = delete;
	BigBomb(BigBomb&& _Other) noexcept = delete;
	BigBomb& operator=(const BigBomb& _Other) = delete;
	BigBomb& operator=(BigBomb&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void DelayUpdate() override;
protected:

private:
	int HP_;
	float4 PrevPos_;
	bool CheckMapCollision();
	GameEngineImage* ColMapImage_;
	GameEngineCollision* BigBombCol_;
	GameEngineRenderer* BigBombRenderer_;
	GameEngineLevel* Level_;

private:
};
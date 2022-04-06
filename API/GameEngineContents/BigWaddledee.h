#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class BigWaddledee : public Monster
{
public:
	BigWaddledee();
	~BigWaddledee();

	BigWaddledee(const BigWaddledee& _Other) = delete;
	BigWaddledee(BigWaddledee&& _Other) noexcept = delete;
	BigWaddledee& operator=(const BigWaddledee& _Other) = delete;
	BigWaddledee& operator=(BigWaddledee&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
protected:

private:
	int HP_;
	float4 PrevPos_;
	bool CheckMapCollision();
	GameEngineImage* ColMapImage_;
	GameEngineCollision* BigWaddledeeCol_;
	GameEngineRenderer* BigWaddledeeRenderer_;
	GameEngineLevel* Level_;

private:
};
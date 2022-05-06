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
	void DelayUpdate() override;
};

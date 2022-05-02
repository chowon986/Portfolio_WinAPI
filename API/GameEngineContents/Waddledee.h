#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class Waddledee : public Monster
{
private:

public:
	Waddledee();
	~Waddledee();

	Waddledee(const Waddledee& _Other) = delete;
	Waddledee(Waddledee&& _Other) noexcept = delete;
	Waddledee& operator=(const Waddledee& _Other) = delete;
	Waddledee& operator=(Waddledee&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
};
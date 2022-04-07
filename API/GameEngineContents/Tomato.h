#pragma once
#include "Item.h"

class GameEngineCollision;
class Player;
class GameEngineRenderer;
class Tomato : public Item
{
public:
	Tomato();
	~Tomato();

	Tomato(const Tomato& _Other) = delete;
	Tomato(Tomato&& _Other) noexcept = delete;
	Tomato& operator=(const Tomato& _Other) = delete;
	Tomato& operator=(Tomato&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* TomatoCol_;
	GameEngineRenderer* TomatoRenderer_;
};
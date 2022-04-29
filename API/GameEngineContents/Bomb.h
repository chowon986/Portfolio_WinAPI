#pragma once
#include "Obstruction.h"

class GameEngineRenderer;
class GameEngineCollision;
class Bomb : public Obstruction
{
public:
	Bomb();
	~Bomb();
	Bomb(const Bomb& _Other) = delete;
	Bomb(Bomb&& _Ohter) noexcept = delete;
	Bomb& operator=(const Bomb& _Other) = delete;
	Bomb& operator=(Bomb&& _Other) noexcept = delete;


protected:
	void Start();
	void Update();

private:
	GameEngineCollision* Collision_;
	GameEngineRenderer* Renderer_;

};

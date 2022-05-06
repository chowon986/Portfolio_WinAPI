#pragma once
#include "Obstruction.h"

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
	void DelayUpdate();
	void ColUpdate() override;
	bool ColOn();

private:
	GameEngineCollision* Collision2_;
	float Time_;
	bool Col_;
};

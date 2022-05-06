#pragma once
#include "Obstruction.h"

class BombBox : public Obstruction
{
public:
	BombBox();
	~BombBox();

	BombBox(const BombBox& _Other) = delete;
	BombBox(BombBox&& _Other) noexcept = delete;
	BombBox& operator=(const BombBox& _Other) = delete;
	BombBox& operator=(BombBox&& _Other) noexcept = delete;


protected:
	void Start();
	void DelayUpdate();
	bool ColOn();

private:
	GameEngineCollision* Collision2_;
	GameEngineCollision* Collision3_;
	GameEngineRenderer* Renderer_;
	float Time_;
	bool Col_;

};

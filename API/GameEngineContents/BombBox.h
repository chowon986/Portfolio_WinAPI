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
	void Update();

private:
	GameEngineRenderer* BombBoxRenderer_;
	GameEngineCollision* BombBoxCol_;
};

#pragma once
#include "Obstruction.h"

class Box : public Obstruction
{
public:
	Box();
	~Box();

	Box(const Box& _Other) = delete;
	Box(Box&& _Other) noexcept = delete;
	Box& operator=(const Box& _Other) = delete;
	Box& operator=(Box&& _Other) noexcept = delete;

protected:
	void Start();
	void Update();

private:
	GameEngineCollision* BoxCol_;
	GameEngineRenderer* BoxRenderer_;

};

#pragma once
#include "Monster.h"

class Box : public Monster
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

private:

};

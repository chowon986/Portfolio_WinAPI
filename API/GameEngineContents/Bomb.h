#pragma once
#include "Monster.h"

class Bomb : public Monster
{
public:
	Bomb();
	~Bomb();

	Bomb(const Bomb& _Other) = delete;
	Bomb(Bomb&& _Other) noexcept = delete;
	Bomb& operator=(const Bomb& _Other) = delete;
	Bomb& operator=(Bomb&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};

#pragma once
#include "Monster.h"

class Storo : public Monster
{
public:
	Storo();
	~Storo();

	Storo(const Storo& _Other) = delete;
	Storo(Storo&& _Other) noexcept = delete;
	Storo& operator=(const Storo& _Other) = delete;
	Storo& operator=(Storo&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
#pragma once
#include "Monster.h"

class Sparky : public Monster
{
public:
	Sparky();
	~Sparky();

	Sparky(const Sparky& _Other) = delete;
	Sparky(Sparky&& _Other) noexcept = delete;
	Sparky& operator=(const Sparky& _Other) = delete;
	Sparky& operator=(Sparky&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
#pragma once
#include "Monster.h"

class Mice : public Monster
{
public:
	Mice();
	~Mice();

	Mice(const Mice& _Other) = delete;
	Mice(Mice&& _Other) noexcept = delete;
	Mice& operator=(const Mice& _Other) = delete;
	Mice& operator=(Mice&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
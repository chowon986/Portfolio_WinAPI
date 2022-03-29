#pragma once
#include "Monster.h"

class Sword : public Monster
{
public:
	Sword();
	~Sword();

	Sword(const Sword& _Other) = delete;
	Sword(Sword&& _Other) noexcept = delete;
	Sword& operator=(const Sword& _Other) = delete;
	Sword& operator=(Sword&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
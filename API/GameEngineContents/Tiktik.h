#pragma once
#include "Monster.h"

class Tiktik : public Monster
{
public:
	Tiktik();
	~Tiktik();

	Tiktik(const Tiktik& _Other) = delete;
	Tiktik(Tiktik&& _Other) noexcept = delete;
	Tiktik& operator=(const Tiktik& _Other) = delete;
	Tiktik& operator=(Tiktik&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
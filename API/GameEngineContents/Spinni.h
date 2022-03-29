#pragma once
#include "Monster.h"

class Spinni : public Monster
{
public:
	Spinni();
	~Spinni();

	Spinni(const Spinni& _Other) = delete;
	Spinni(Spinni&& _Other) noexcept = delete;
	Spinni& operator=(const Spinni& _Other) = delete;
	Spinni& operator=(Spinni&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
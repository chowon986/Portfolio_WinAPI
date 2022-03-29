#pragma once
#include "Monster.h"

class Brontobert : public Monster
{
public:
	Brontobert();
	~Brontobert();

	Brontobert(const Brontobert& _Other) = delete;
	Brontobert(Brontobert&& _Other) noexcept = delete;
	Brontobert& operator=(const Brontobert& _Other) = delete;
	Brontobert& operator=(Brontobert&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};

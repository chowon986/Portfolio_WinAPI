#pragma once
#include "Monster.h"

class Doroach : public Monster
{
public:
	Doroach();
	~Doroach();

	Doroach(const Doroach& _Other) = delete;
	Doroach(Doroach&& _Other) noexcept = delete;
	Doroach& operator=(const Doroach& _Other) = delete;
	Doroach& operator=(Doroach&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};

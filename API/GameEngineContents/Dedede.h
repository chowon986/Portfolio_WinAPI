#pragma once
#include "Monster.h"

class Dedede : public Monster
{
public:
	Dedede();
	~Dedede();

	Dedede(const Dedede& _Other) = delete;
	Dedede(Dedede&& _Other) noexcept = delete;
	Dedede& operator=(const Dedede& _Other) = delete;
	Dedede& operator=(Dedede&& _Other) noexcept = delete;

public:
	void Start();
protected:

private:

};

#pragma once
#include "Monster.h"

class Frosty : public Monster
{
public:
	Frosty();
	~Frosty();

	Frosty(const Frosty& _Other) = delete;
	Frosty(Frosty&& _Other) noexcept = delete;
	Frosty& operator=(const Frosty& _Other) = delete;
	Frosty& operator=(Frosty&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
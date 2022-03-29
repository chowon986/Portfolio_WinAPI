#pragma once
#include "Monster.h"

class BigBomb : public Monster
{
public:
	BigBomb();
	~BigBomb();

	BigBomb(const BigBomb& _Other) = delete;
	BigBomb(BigBomb&& _Other) noexcept = delete;
	BigBomb& operator=(const BigBomb& _Other) = delete;
	BigBomb& operator=(BigBomb&& _Other) noexcept = delete;

public: 
	void Start();
protected:

private:

};

#pragma once
#include "Monster.h"

class Moon : public Monster
{
public:
	Moon();
	~Moon();

	Moon(const Moon& _Other) = delete;
	Moon(Moon&& _Other) noexcept = delete;
	Moon& operator=(const Moon& _Other) = delete;
	Moon& operator=(Moon&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
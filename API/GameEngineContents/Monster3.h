#pragma once
#include "Monster.h"

class Monster3 : public Monster
{
public:
	Monster3();
	~Monster3();

	Monster3(const Monster3& _Other) = delete;
	Monster3(Monster3&& _Other) noexcept = delete;
	Monster3& operator=(const Monster3& _Other) = delete;
	Monster3& operator=(Monster3&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
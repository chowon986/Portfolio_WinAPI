#pragma once
#include "Monster.h"

class Animal : public Monster
{
public:
	Animal();
	~Animal();

	Animal(const Animal& _Other) = delete;
	Animal(Animal&& _Other) noexcept = delete;
	Animal& operator=(const Animal& _Other) = delete;
	Animal& operator=(Animal&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
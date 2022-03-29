#pragma once
#include "Monster.h"

class Tomato : public Monster
{
public:
	Tomato();
	~Tomato();

	Tomato(const Tomato& _Other) = delete;
	Tomato(Tomato&& _Other) noexcept = delete;
	Tomato& operator=(const Tomato& _Other) = delete;
	Tomato& operator=(Tomato&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
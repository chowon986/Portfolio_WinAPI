#pragma once
#include "GameEngine/GameEngineActor.h"

class Obstruction : public GameEngineActor
{
public:
	Obstruction();
	~Obstruction();
	Obstruction(const Obstruction& _Other) = delete;
	Obstruction(Obstruction&& _Other) noexcept = delete;
	Obstruction& operator=(const Obstruction& _Other) = delete;
	Obstruction& operator=(Obstruction&& _Other) noexcept = delete;

public:
	void SetHP(int _HP);
	int GetHP();
private:
	int HP_;
};


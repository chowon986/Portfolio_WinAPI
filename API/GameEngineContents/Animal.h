#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class Player;
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
	void Start() override;
	void UpdateMove() override;
	void DelayUpdate() override;

};
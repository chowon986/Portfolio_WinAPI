#pragma once
#include "Monster.h"

class GameEngineRenderer;
class BigTreasureChest : public Monster
{
public:
	BigTreasureChest();
	~BigTreasureChest();

	BigTreasureChest(const BigTreasureChest& _Other) = delete;
	BigTreasureChest(BigTreasureChest&& _Other) noexcept = delete;
	BigTreasureChest& operator=(const BigTreasureChest& _Other) = delete;
	BigTreasureChest& operator=(BigTreasureChest&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* BigTreasureChestCol_;
	GameEngineRenderer* BigTreasureChestRenderer_;
};
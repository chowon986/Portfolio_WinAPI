#pragma once
#include "Monster.h"

class GameEngineRenderer;
class TreasureChest : public Monster
{
public:
	TreasureChest();
	~TreasureChest();

	TreasureChest(const TreasureChest& _Other) = delete;
	TreasureChest(TreasureChest&& _Other) noexcept = delete;
	TreasureChest& operator=(const TreasureChest& _Other) = delete;
	TreasureChest& operator=(TreasureChest&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* TreasureChestCol_;
	GameEngineRenderer* TreasureChestRenderer_;
};
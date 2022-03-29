#pragma once
#include "Monster.h"

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

protected:

private:

};
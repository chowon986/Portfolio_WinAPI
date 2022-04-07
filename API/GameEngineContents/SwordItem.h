#pragma once
#include "Item.h"

class GameEngineCollision;
class Player;
class GameEngineRenderer;
class SwordItem : public Item
{
public:
	SwordItem();
	~SwordItem();

	SwordItem(const SwordItem& _Other) = delete;
	SwordItem(SwordItem&& _Other) noexcept = delete;
	SwordItem& operator=(const SwordItem& _Other) = delete;
	SwordItem& operator=(SwordItem&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* SwordItemCol_;
	GameEngineRenderer* SwordItemRenderer_;
};
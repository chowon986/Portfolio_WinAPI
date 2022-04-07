#pragma once
#include "Item.h"

class GameEngineCollision;
class Player;
class GameEngineRenderer;
class FireItem : public Item
{
public:
	FireItem();
	~FireItem();

	FireItem(const FireItem& _Other) = delete;
	FireItem(FireItem&& _Other) noexcept = delete;
	FireItem& operator=(const FireItem& _Other) = delete;
	FireItem& operator=(FireItem&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* FireItemCol_;
	GameEngineRenderer* FireItemRenderer_;
};
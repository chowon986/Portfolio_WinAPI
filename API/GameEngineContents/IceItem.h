#pragma once
#include "Item.h"

class GameEngineCollision;
class Player;
class GameEngineRenderer;
class IceItem : public Item
{
public:
	IceItem();
	~IceItem();

	IceItem(const IceItem& _Other) = delete;
	IceItem(IceItem&& _Other) noexcept = delete;
	IceItem& operator=(const IceItem& _Other) = delete;
	IceItem& operator=(IceItem&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* IceItemCol_;
	GameEngineRenderer* IceItemRenderer_;
};
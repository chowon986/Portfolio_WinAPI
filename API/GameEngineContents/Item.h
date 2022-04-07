#pragma once
#include "GameEngine/GameEngineActor.h"

class Item : public GameEngineActor
{
public:
	Item();
	~Item();
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

public:

private:

};


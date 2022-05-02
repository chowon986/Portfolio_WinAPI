#pragma once
#include "Item.h"
#include <GameEngineBase/GameEngineSound.h>


class GameEngineCollision;
class Player;
class GameEngineRenderer;
class HPUp : public Item
{
public:
	HPUp();
	~HPUp();

	HPUp(const HPUp& _Other) = delete;
	HPUp(HPUp&& _Other) noexcept = delete;
	HPUp& operator=(const HPUp& _Other) = delete;
	HPUp& operator=(HPUp&& _Other) noexcept = delete;

public:
	void Start();
	void Update();

protected:

private:
	GameEngineCollision* HPUpCol_;
	GameEngineRenderer* HPUpRenderer_;
	GameEngineSoundPlayer BgmPlayer_;
};
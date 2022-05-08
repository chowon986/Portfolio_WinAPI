#pragma once
#include "Obstruction.h"
#include <GameEngineBase/GameEngineSound.h>

class BombBomb : public Obstruction
{
public:
	BombBomb();
	~BombBomb();

	BombBomb(const BombBomb& _Other) = delete;
	BombBomb(BombBomb&& _Other) noexcept = delete;
	BombBomb& operator=(const BombBomb& _Other) = delete;
	BombBomb& operator=(BombBomb&& _Other) noexcept = delete;

protected:
	void Start();
	void DelayUpdate();
	void ColUpdate() override;

private:

public:
};

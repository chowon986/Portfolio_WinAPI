#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEngineCollision;
class Level2 : public GameEngineLevelBase
{
public:
	Level2();
	~Level2();

	Level2(const Level2& _Other) = delete;
	Level2(Level2&& _Other) noexcept = delete;
	Level2& operator=(const Level2& _Other) = delete;
	Level2& operator=(Level2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol2_2;
};


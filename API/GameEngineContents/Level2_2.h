#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_2 : public GameEngineLevelBase
{
public:
	Level2_2();
	~Level2_2();

	Level2_2(const Level2_2& _Other) = delete;
	Level2_2(Level2_2&& _Other) noexcept = delete;
	Level2_2& operator=(const Level2_2& _Other) = delete;
	Level2_2& operator=(Level2_2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol2_3;
};


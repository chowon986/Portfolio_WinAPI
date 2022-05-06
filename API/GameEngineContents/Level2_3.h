#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_3 : public GameEngineLevelBase
{
public:

	Level2_3();
	~Level2_3();

	Level2_3(const Level2_3& _Other) = delete;
	Level2_3(Level2_3&& _Other) noexcept = delete;
	Level2_3& operator=(const Level2_3& _Other) = delete;
	Level2_3& operator=(Level2_3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol2_4;
};


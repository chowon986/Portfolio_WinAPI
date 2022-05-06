#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_4 : public GameEngineLevelBase
{
public:
	Level2_4();
	~Level2_4();

	Level2_4(const Level2_4& _Other) = delete;
	Level2_4(Level2_4&& _Other) noexcept = delete;
	Level2_4& operator=(const Level2_4& _Other) = delete;
	Level2_4& operator=(Level2_4&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol2_5;
};


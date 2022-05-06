#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_5 : public GameEngineLevelBase
{
public:
	Level2_5();
	~Level2_5();

	Level2_5(const Level2_5& _Other) = delete;
	Level2_5(Level2_5&& _Other) noexcept = delete;
	Level2_5& operator=(const Level2_5& _Other) = delete;
	Level2_5& operator=(Level2_5&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* Cannon_;
};


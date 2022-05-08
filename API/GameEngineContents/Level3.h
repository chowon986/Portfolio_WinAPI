#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class Level3 : public GameEngineLevelBase
{
public:
	Level3();
	~Level3();

	Level3(const Level3& _Other) = delete;
	Level3(Level3&& _Other) noexcept = delete;
	Level3& operator=(const Level3& _Other) = delete;
	Level3& operator=(Level3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* Boss;
};


#pragma once
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class Level1_3 : public GameEngineLevelBase
{
public:
	
	Level1_3();
	~Level1_3();

	Level1_3(const Level1_3& _Other) = delete;
	Level1_3(Level1_3&& _Other) noexcept = delete;
	Level1_3& operator=(const Level1_3& _Other) = delete;
	Level1_3& operator=(Level1_3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol1_4;
};


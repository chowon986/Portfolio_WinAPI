#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEngineCollision;
class GameEngineImage;
class MonBotUI;
class Level1 : public GameEngineLevelBase
{
public:
	Level1();
	~Level1();

	Level1(const Level1& _Other) = delete;
	Level1(Level1&& _Other) noexcept = delete;
	Level1& operator=(const Level1& _Other) = delete;
	Level1& operator=(Level1&& _Other) noexcept = delete;



protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	MonBotUI* MonsterStatus_;
	GameEngineCollision* DoorCol1_2;
	GameEngineImage* ColMapImage_;


private:
};


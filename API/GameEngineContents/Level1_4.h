#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineLevelBase.h"

class Player;
class BotUI;
class GameEngineCollision;
class Level1_4 : public GameEngineLevelBase
{
public:

	Level1_4();
	~Level1_4();

	Level1_4(const Level1_4& _Other) = delete;
	Level1_4(Level1_4&& _Other) noexcept = delete;
	Level1_4& operator=(const Level1_4& _Other) = delete;
	Level1_4& operator=(Level1_4&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* Cannon_;
	GameEngineSoundPlayer BgmPlayer_;
};


#pragma once
#include "GameEngineLevelBase.h"
#include <GameEngineBase/GameEngineSound.h>


class GameEngineImage;
class GameEngineSoundPlayer;
class GameOver : public GameEngineLevelBase
{
public:
	GameOver();
	~GameOver();

	GameOver(const GameOver& _Other) = delete;
	GameOver(GameOver&& _Other) noexcept = delete;
	GameOver& operator=(const GameOver& _Other) = delete;
	GameOver& operator=(GameOver&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineSoundPlayer BgmPlayer;
};


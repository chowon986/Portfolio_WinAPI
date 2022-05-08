#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineLevelBase.h"

class VideoPlayer;
class GameEngineSoundPlayer;
class BeforeTitleLevel : public GameEngineLevelBase
{
public:
	BeforeTitleLevel();
	~BeforeTitleLevel();

	BeforeTitleLevel(const BeforeTitleLevel& _Other) = delete;
	BeforeTitleLevel(BeforeTitleLevel&& _Other) noexcept = delete;
	BeforeTitleLevel& operator=(const BeforeTitleLevel& _Other) = delete;
	BeforeTitleLevel& operator=(BeforeTitleLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void DelayUpdate() override;

private:
	GameEngineSoundPlayer BgmPlayer;
	VideoPlayer* BeforeTitleVideo_;
};


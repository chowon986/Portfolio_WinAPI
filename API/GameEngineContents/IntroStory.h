#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineLevelBase.h"

class VideoPlayer;
class IntroStory : public GameEngineLevelBase
{
public:
	IntroStory();
	~IntroStory();

	IntroStory(const IntroStory& _Other) = delete;
	IntroStory(IntroStory&& _Other) noexcept = delete;
	IntroStory& operator=(const IntroStory& _Other) = delete;
	IntroStory& operator=(IntroStory&& _Other) noexcept = delete;
protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	VideoPlayer* IntroVideo_;
	float Time;
	GameEngineSoundPlayer BgmPlayer;
};


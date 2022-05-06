#pragma once
#include "GameEngineLevelBase.h"

class VideoPlayer;
class EndingStory : public GameEngineLevelBase
{
public:
	EndingStory();
	~EndingStory();

	EndingStory(const EndingStory& _Other) = delete;
	EndingStory(EndingStory&& _Other) noexcept = delete;
	EndingStory& operator=(const EndingStory& _Other) = delete;
	EndingStory& operator=(EndingStory&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	VideoPlayer* EndingVideo_;
};


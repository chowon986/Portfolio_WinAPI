#pragma once
#include <GameEngine/GameEngineLevel.h>

class VideoPlayer;
class EndingStory : public GameEngineLevel
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
	void Update() override;
	void LevelChangeStart() override;

private:
	VideoPlayer* EndingVideo_;
};


#pragma once
#include <GameEngine/GameEngineLevel.h>

class VideoPlayer;
class IntroStory : public GameEngineLevel
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
	void Update() override;
	void LevelChangeStart() override;

private:
	VideoPlayer* IntroVideo_;
};


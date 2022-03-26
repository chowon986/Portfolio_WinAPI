#pragma once
#include <GameEngine/GameEngineLevel.h>

class IntroStoryLevel : public GameEngineLevel
{	
public:
	IntroStoryLevel();

	virtual ~IntroStoryLevel();

	IntroStoryLevel(const IntroStoryLevel& _Other) = delete;
	IntroStoryLevel(IntroStoryLevel&& _Other) noexcept = delete;
	IntroStoryLevel& operator=(const IntroStoryLevel& _Other) = delete;
	IntroStoryLevel& operator=(IntroStoryLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;

	void LevelChangeStart() override;

	void Update() override;
};


#pragma once
#include <GameEngine/GameEngineLevel.h>

class EndingStoryLevel : public GameEngineLevel
{
public:
	EndingStoryLevel();

	virtual ~EndingStoryLevel();

	EndingStoryLevel(const EndingStoryLevel& _Other) = delete;
	EndingStoryLevel(EndingStoryLevel&& _Other) noexcept = delete;
	EndingStoryLevel& operator=(const EndingStoryLevel& _Other) = delete;
	EndingStoryLevel& operator=(EndingStoryLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;

	void LevelChangeStart() override;

	void Update() override;
};


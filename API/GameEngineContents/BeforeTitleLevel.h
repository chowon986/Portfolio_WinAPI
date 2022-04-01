#pragma once
#include <GameEngine/GameEngineLevel.h>

class VideoPlayer;
class BeforeTitleLevel : public GameEngineLevel
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
	void Update() override;
	void LevelChangeStart() override;

private:
	VideoPlayer* BeforeTitleVideo_;
};


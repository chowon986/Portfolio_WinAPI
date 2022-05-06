#pragma once
#include "GameEngineLevelBase.h"

class AnimationKirby;
class GameEngineRenderer;
class DanceStage : public GameEngineLevelBase
{
public:
	DanceStage();
	~DanceStage();

	DanceStage(const DanceStage& _Other) = delete;
	DanceStage(DanceStage&& _Other) noexcept = delete;
	DanceStage& operator=(const DanceStage& _Other) = delete;
	DanceStage& operator=(DanceStage&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	AnimationKirby* AnimationKirby_;
	GameEngineRenderer* AlphaRenderer_;
};


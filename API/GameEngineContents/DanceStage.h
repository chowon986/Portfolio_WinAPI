#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

class Player;
class GameEngineRenderer;
class DanceStage : public GameEngineLevel
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
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	Player* Player_;
	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* BasicRenderer_;
	GameEngineRenderer* DanceKirbyRenderer;
	GameEngineSoundPlayer BgmPlayer_;

};


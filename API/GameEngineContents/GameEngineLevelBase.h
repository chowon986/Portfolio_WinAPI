#pragma once
#include <GameEngine/GameEngineLevel.h>

class GameEngineRenderer;
class GameEngineLevelBase : public GameEngineLevel
{
public:
	static int MAJOR_LEVEL;
public:
	GameEngineLevelBase();
	~GameEngineLevelBase();

	GameEngineLevelBase(const GameEngineLevelBase& _Other) = delete;
	GameEngineLevelBase(GameEngineLevelBase&& _Other) noexcept = delete;
	GameEngineLevelBase& operator=(const GameEngineLevelBase& _Other) = delete;
	GameEngineLevelBase& operator=(GameEngineLevelBase&& _Other) noexcept = delete;

protected:
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	virtual void DelayUpdate() {}

protected:
	GameEngineRenderer* AlphaRenderer_;
	float DelayTime_;
	float ElapsedTime_;
};


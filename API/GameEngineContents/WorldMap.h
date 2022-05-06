#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineLevelBase.h"


class BotUI;
class Player;
class WorldMap : public GameEngineLevelBase
{
public:
	WorldMap();
	~WorldMap();

	WorldMap(const WorldMap& _Other) = delete;
	WorldMap(WorldMap&& _Other) noexcept = delete;
	WorldMap& operator=(const WorldMap& _Other) = delete;
	WorldMap& operator=(WorldMap&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void DelayUpdate() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	BotUI* PlayerStatus_;
	BotUI* PlayerStatus2_;
	Player* Player_;
	Player* Player2_;
	GameEngineCollision* Star1_;
	GameEngineRenderer* WorldMapStarRenderer1;
	GameEngineRenderer* WorldMapStarRenderer2;
	GameEngineRenderer* ExplainRenderer_;
	GameEngineRenderer* ExplainRenderer2_;
	GameEngineRenderer* ExplainRenderer3_;
	GameEngineRenderer* ExplainRenderer4_;
	GameEngineRenderer* BombRenderer_;
	GameEngineRenderer* LittleStarRenderer;
	GameEngineRenderer* LittleStarRenderer2;
	GameEngineRenderer* ChooseLevel1_;
	GameEngineRenderer* ChooseLevel2_;
	GameEngineSoundPlayer BgmPlayer_;
	int Level_;
	int MajorLevel_;
};


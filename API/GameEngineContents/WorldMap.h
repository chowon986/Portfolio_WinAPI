#pragma once
#include <GameEngine/GameEngineLevel.h>

class BotUI;
class Player;
class WorldMap : public GameEngineLevel
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
	void Update() override;
	void LevelChangeStart() override;

private:
	BotUI* PlayerStatus_;
	Player* Player_;
	Player* Player2_;
	GameEngineCollision* Star1_;
	GameEngineRenderer* WorldMapStarRenderer1;
	GameEngineRenderer* LittleStarRenderer;
	GameEngineRenderer* LittleStarRenderer2;
	GameEngineRenderer* ChooseLevel1_;

};


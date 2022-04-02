#pragma once
#include <GameEngine/GameEngineLevel.h>

class BotUI;
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
	BotUI* PlayerUI_;
};


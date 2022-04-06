#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEngineCollision;
class Level2 : public GameEngineLevel
{
public:
	float GetMapSizeY() override;
	float GetMapSizeX() override;

public:
	Level2();
	~Level2();

	Level2(const Level2& _Other) = delete;
	Level2(Level2&& _Other) noexcept = delete;
	Level2& operator=(const Level2& _Other) = delete;
	Level2& operator=(Level2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	float MapSizeX_;
	float MapSizeY_;
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* DoorCol2_2;
};


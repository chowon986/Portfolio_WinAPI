#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_5 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;

	Level2_5();
	~Level2_5();

	Level2_5(const Level2_5& _Other) = delete;
	Level2_5(Level2_5&& _Other) noexcept = delete;
	Level2_5& operator=(const Level2_5& _Other) = delete;
	Level2_5& operator=(Level2_5&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	float MapSizeX_;
	float MapSizeY_;
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* DoorCol2_5;
};


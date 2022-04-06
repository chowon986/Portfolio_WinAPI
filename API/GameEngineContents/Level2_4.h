#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_4 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;

	Level2_4();
	~Level2_4();

	Level2_4(const Level2_4& _Other) = delete;
	Level2_4(Level2_4&& _Other) noexcept = delete;
	Level2_4& operator=(const Level2_4& _Other) = delete;
	Level2_4& operator=(Level2_4&& _Other) noexcept = delete;

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


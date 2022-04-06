#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEngineRenderer;
class Level1_2 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;


	Level1_2();
	~Level1_2();

	Level1_2(const Level1_2& _Other) = delete;
	Level1_2(Level1_2&& _Other) noexcept = delete;
	Level1_2& operator=(const Level1_2& _Other) = delete;
	Level1_2& operator=(Level1_2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	Player* Player_;
	BotUI* PlayerUI_;
	float MapSizeX_;
	float MapSizeY_;
	GameEngineRenderer* MonsterRenderer_;
	GameEngineCollision* DoorCol1_3;

};


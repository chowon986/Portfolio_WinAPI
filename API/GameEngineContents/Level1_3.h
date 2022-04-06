#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level1_3 : public GameEngineLevel
{
public:
	float GetMapSizeY() override;
	float GetMapSizeX() override;
	
	Level1_3();
	~Level1_3();

	Level1_3(const Level1_3& _Other) = delete;
	Level1_3(Level1_3&& _Other) noexcept = delete;
	Level1_3& operator=(const Level1_3& _Other) = delete;
	Level1_3& operator=(Level1_3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	Player* Player_;
	BotUI* PlayerUI_;
	float MapSizeX_;
	float MapSizeY_;
	GameEngineCollision* DoorCol1_4;
};


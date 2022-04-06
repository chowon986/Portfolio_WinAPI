#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level3_2 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;

	Level3_2();
	~Level3_2();

	Level3_2(const Level3_2& _Other) = delete;
	Level3_2(Level3_2&& _Other) noexcept = delete;
	Level3_2& operator=(const Level3_2& _Other) = delete;
	Level3_2& operator=(Level3_2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	float MapSizeX_;
	float MapSizeY_;
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* Level3_3;

};


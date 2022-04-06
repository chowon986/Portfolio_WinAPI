#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level3_5 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;

	Level3_5();
	~Level3_5();

	Level3_5(const Level3_5& _Other) = delete;
	Level3_5(Level3_5&& _Other) noexcept = delete;
	Level3_5& operator=(const Level3_5& _Other) = delete;
	Level3_5& operator=(Level3_5&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	float MapSizeX_;
	float MapSizeY_;
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* Level3_6;

};


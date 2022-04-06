#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level3 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;

	Level3();
	~Level3();

	Level3(const Level3& _Other) = delete;
	Level3(Level3&& _Other) noexcept = delete;
	Level3& operator=(const Level3& _Other) = delete;
	Level3& operator=(Level3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	float MapSizeX_;
	float MapSizeY_;
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* Level3_2;

};


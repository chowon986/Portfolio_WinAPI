#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level3_3 : public GameEngineLevel
{
public:
	float GetMapSizeX() override;
	float GetMapSizeY() override;

	Level3_3();
	~Level3_3();

	Level3_3(const Level3_3& _Other) = delete;
	Level3_3(Level3_3&& _Other) noexcept = delete;
	Level3_3& operator=(const Level3_3& _Other) = delete;
	Level3_3& operator=(Level3_3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	float MapSizeX_;
	float MapSizeY_;
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* Level3_4;

};


#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_3 : public GameEngineLevel
{
public:

	Level2_3();
	~Level2_3();

	Level2_3(const Level2_3& _Other) = delete;
	Level2_3(Level2_3&& _Other) noexcept = delete;
	Level2_3& operator=(const Level2_3& _Other) = delete;
	Level2_3& operator=(Level2_3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol2_4;
};


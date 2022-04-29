#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEgnineCollision;
class Level2_4 : public GameEngineLevel
{
public:
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
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* DoorCol2_5;
};


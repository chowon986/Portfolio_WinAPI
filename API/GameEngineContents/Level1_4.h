#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class GameEngineCollision;
class Level1_4 : public GameEngineLevel
{
public:

	Level1_4();
	~Level1_4();

	Level1_4(const Level1_4& _Other) = delete;
	Level1_4(Level1_4&& _Other) noexcept = delete;
	Level1_4& operator=(const Level1_4& _Other) = delete;
	Level1_4& operator=(Level1_4&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	Player* Player_;
	BotUI* PlayerStatus_;
	GameEngineCollision* Cannon_;
};


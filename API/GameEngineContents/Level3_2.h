#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level3_2 : public GameEngineLevel
{
public:

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
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* Level3_3;

};


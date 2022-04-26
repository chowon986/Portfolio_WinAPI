#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class BotUI;
class Level3_4 : public GameEngineLevel
{
public:
	Level3_4();
	~Level3_4();

	Level3_4(const Level3_4& _Other) = delete;
	Level3_4(Level3_4&& _Other) noexcept = delete;
	Level3_4& operator=(const Level3_4& _Other) = delete;
	Level3_4& operator=(Level3_4&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	Player* Player_;
	BotUI* PlayerUI_;
	GameEngineCollision* Level3_5;

};


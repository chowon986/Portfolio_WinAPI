#pragma once
#include <GameEngine/GameEngineLevel.h>

class Player;
class Background;
class GameEngineImage;
class GameEngineRenderer;
class BotUI;
class Dedede;
class Boss : public GameEngineLevel
{
public:
	Boss();
	~Boss();

	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Background* BossLevelStart_;
	Background* BossLevelEnd_;
	GameEngineRenderer* BossLevelStartRenderer_;
	GameEngineRenderer* BossLevelEndRenderer_;
	GameEngineImage* BossLevelStartImage_;
	GameEngineImage* BossLevelEndImage_;
	GameEngineImage* ColMapImage_;
	Player* Player_;
	BotUI* PlayerStatus_;
	Dedede* Dedede_;
};


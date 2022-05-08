#pragma once
#include "GameEngineLevelBase.h"
#include <GameEngineBase/GameEngineSound.h>

class Player;
class Background;
class GameEngineImage;
class GameEngineRenderer;
class BotUI;
class Dedede;
class GameEngineSound;
class StarMonster;
class Boss : public GameEngineLevelBase
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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

	void DelayUpdate() override;

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
	StarMonster* StarMonster_;
	GameEngineSoundPlayer BgmPlayer;
};


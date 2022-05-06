#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineLevelBase.h"

class GameEngineRenderer;
class GameEngineCollision;
class Player;
class GameEngineImage;
class DieEffect;
class GameEngineSoundPlayer;
class Cannon : public GameEngineLevelBase
{
public:
	Cannon();
	~Cannon();

	Cannon(const Cannon& _Other) = delete;
	Cannon(Cannon&& _Other) noexcept = delete;
	Cannon& operator=(const Cannon& _Other) = delete;
	Cannon& operator=(Cannon&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void DelayUpdate() override;

private:
	GameEngineRenderer* CanRenderer_;
	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* CannonRenderer_;
	GameEngineRenderer* TomatoRenderer_;
	GameEngineCollision* CanCol_;
	Player* Player_;
	float4 PrevPos_;
	GameEngineSoundPlayer BgmPlayer_;
	float Time_;
	bool Rotation_;
	int Index_;
};


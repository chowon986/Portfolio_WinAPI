#pragma once
#include <GameEngine/GameEngineLevel.h>

class GameEngineRenderer;
class GameEngineCollision;
class Player;
class GameEngineImage;
class DieEffect;
class Cannon : public GameEngineLevel
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
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineRenderer* CanRenderer_;
	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* CannonRenderer_;
	GameEngineRenderer* TomatoRenderer_;
	GameEngineCollision* CanCol_;
	Player* Player_;
	float4 PrevPos_;
};


#pragma once
#include "Monster.h"

class Player;
class GameEngineImage;
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class Waddledi : public Monster
{
private:
	Player* Player_;
	GameEngineImage* ColMapImage_;
	GameEngineCollision* WaddlediCol_;
	GameEngineCollision* RightDirCol_;
	GameEngineCollision* LeftDirCol_;
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* EffectRenderer_;
	GameEngineLevel* Level_;
	float4 Dir_;

public:
	Waddledi();
	~Waddledi();

	Waddledi(const Waddledi& _Other) = delete;
	Waddledi(Waddledi&& _Other) noexcept = delete;
	Waddledi& operator=(const Waddledi& _Other) = delete;
	Waddledi& operator=(Waddledi&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
	bool IsDie();
	void Die();
	void UpdateMove();
	void SetDir(float4 _Dir) { Dir_ = _Dir; }

};
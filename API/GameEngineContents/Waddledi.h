#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class Player;
class Waddledi : public Monster
{
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
	void SetState(MonsterState _PrevState);

	void UpdateWalk();
	void UpdateMove();
protected:

private:
	Player* Player_;
	float4 PrevPos_;
	bool CheckMapCollision();
	GameEngineImage* ColMapImage_;
	GameEngineCollision* WaddlediCol_;
	GameEngineRenderer* WaddlediRenderer_;
	GameEngineLevel* Level_;
	float4 Dir_;

private:
};
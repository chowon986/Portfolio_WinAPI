#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
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
protected:

private:
	int HP_;
	float4 PrevPos_;
	bool CheckMapCollision();
	GameEngineImage* ColMapImage_;
	GameEngineCollision* WaddlediCol_;
	GameEngineRenderer* WaddlediRenderer_;
	GameEngineLevel* Level_;

private:
};
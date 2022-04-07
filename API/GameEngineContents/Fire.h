#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class GameEngineCollision;
class Fire : public Monster
{
public:
	Fire();
	~Fire();

	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
protected:

private:
	GameEngineImage* ColMapImage_;
	bool CheckMapCollision();
	float4 PrevPos_;
	GameEngineLevel* Level_;
	GameEngineRenderer* FireRenderer_;
	GameEngineCollision* FireCol_;
	GameEngineImage* FireImage_;
};
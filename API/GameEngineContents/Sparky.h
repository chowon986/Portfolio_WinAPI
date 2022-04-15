#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Sparky : public Monster
{
public:
	Sparky();
	~Sparky();

	Sparky(const Sparky& _Other) = delete;
	Sparky(Sparky&& _Other) noexcept = delete;
	Sparky& operator=(const Sparky& _Other) = delete;
	Sparky& operator=(Sparky&& _Other) noexcept = delete;

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
	float4 Dir_;
	void UpdateMove();
};
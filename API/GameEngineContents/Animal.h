#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class Animal : public Monster
{
public:
	Animal();
	~Animal();

	Animal(const Animal& _Other) = delete;
	Animal(Animal&& _Other) noexcept = delete;
	Animal& operator=(const Animal& _Other) = delete;
	Animal& operator=(Animal&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
protected:

private:
	int HP_;
	float4 PrevPos_;
	GameEngineLevel* Level_;
	GameEngineImage* ColMapImage_;
	GameEngineCollision* AnimalCol_;
	GameEngineRenderer* AnimalRenderer_;

	bool CheckMapCollision();

private:
};
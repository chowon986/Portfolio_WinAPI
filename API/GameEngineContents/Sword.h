#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Sword : public Monster
{
public:
	Sword();
	~Sword();

	Sword(const Sword& _Other) = delete;
	Sword(Sword&& _Other) noexcept = delete;
	Sword& operator=(const Sword& _Other) = delete;
	Sword& operator=(Sword&& _Other) noexcept = delete;

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
};
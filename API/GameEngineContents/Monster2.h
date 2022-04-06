#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Monster2 : public Monster
{
public:
	Monster2();
	~Monster2();

	Monster2(const Monster2& _Other) = delete;
	Monster2(Monster2&& _Other) noexcept = delete;
	Monster2& operator=(const Monster2& _Other) = delete;
	Monster2& operator=(Monster2&& _Other) noexcept = delete;

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

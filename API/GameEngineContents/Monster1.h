#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Monster1 : public Monster
{
public:
	Monster1();
	~Monster1();

	Monster1(const Monster1& _Other) = delete;
	Monster1(Monster1&& _Other) noexcept = delete;
	Monster1& operator=(const Monster1& _Other) = delete;
	Monster1& operator=(Monster1&& _Other) noexcept = delete;

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

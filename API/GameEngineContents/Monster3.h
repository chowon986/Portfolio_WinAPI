#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Monster3 : public Monster
{
public:
	Monster3();
	~Monster3();

	Monster3(const Monster3& _Other) = delete;
	Monster3(Monster3&& _Other) noexcept = delete;
	Monster3& operator=(const Monster3& _Other) = delete;
	Monster3& operator=(Monster3&& _Other) noexcept = delete;

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

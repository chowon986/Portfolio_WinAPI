#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Storo : public Monster
{
public:
	Storo();
	~Storo();

	Storo(const Storo& _Other) = delete;
	Storo(Storo&& _Other) noexcept = delete;
	Storo& operator=(const Storo& _Other) = delete;
	Storo& operator=(Storo&& _Other) noexcept = delete;

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
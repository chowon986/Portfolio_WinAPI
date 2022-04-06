#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Tiktik : public Monster
{
public:
	Tiktik();
	~Tiktik();

	Tiktik(const Tiktik& _Other) = delete;
	Tiktik(Tiktik&& _Other) noexcept = delete;
	Tiktik& operator=(const Tiktik& _Other) = delete;
	Tiktik& operator=(Tiktik&& _Other) noexcept = delete;

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
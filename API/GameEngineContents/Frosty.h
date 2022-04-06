#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Frosty : public Monster
{
public:
	Frosty();
	~Frosty();

	Frosty(const Frosty& _Other) = delete;
	Frosty(Frosty&& _Other) noexcept = delete;
	Frosty& operator=(const Frosty& _Other) = delete;
	Frosty& operator=(Frosty&& _Other) noexcept = delete;

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
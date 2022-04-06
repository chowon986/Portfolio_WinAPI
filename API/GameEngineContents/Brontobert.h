#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Brontobert : public Monster
{
public:
	Brontobert();
	~Brontobert();

	Brontobert(const Brontobert& _Other) = delete;
	Brontobert(Brontobert&& _Other) noexcept = delete;
	Brontobert& operator=(const Brontobert& _Other) = delete;
	Brontobert& operator=(Brontobert&& _Other) noexcept = delete;

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
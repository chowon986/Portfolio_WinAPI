#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Doroach : public Monster
{
public:
	Doroach();
	~Doroach();

	Doroach(const Doroach& _Other) = delete;
	Doroach(Doroach&& _Other) noexcept = delete;
	Doroach& operator=(const Doroach& _Other) = delete;
	Doroach& operator=(Doroach&& _Other) noexcept = delete;

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
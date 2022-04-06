#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Spinni : public Monster
{
public:
	Spinni();
	~Spinni();

	Spinni(const Spinni& _Other) = delete;
	Spinni(Spinni&& _Other) noexcept = delete;
	Spinni& operator=(const Spinni& _Other) = delete;
	Spinni& operator=(Spinni&& _Other) noexcept = delete;

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
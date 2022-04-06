#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Waddledoo : public Monster
{
public:
	Waddledoo();
	~Waddledoo();

	Waddledoo(const Waddledoo& _Other) = delete;
	Waddledoo(Waddledoo&& _Other) noexcept = delete;
	Waddledoo& operator=(const Waddledoo& _Other) = delete;
	Waddledoo& operator=(Waddledoo&& _Other) noexcept = delete;

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

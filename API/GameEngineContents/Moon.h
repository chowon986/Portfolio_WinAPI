#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Moon : public Monster
{
public:
	Moon();
	~Moon();

	Moon(const Moon& _Other) = delete;
	Moon(Moon&& _Other) noexcept = delete;
	Moon& operator=(const Moon& _Other) = delete;
	Moon& operator=(Moon&& _Other) noexcept = delete;

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
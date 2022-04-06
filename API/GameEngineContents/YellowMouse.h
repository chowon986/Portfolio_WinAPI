#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class YellowMouse : public Monster
{
public:
	YellowMouse();
	~YellowMouse();

	YellowMouse(const YellowMouse& _Other) = delete;
	YellowMouse(YellowMouse&& _Other) noexcept = delete;
	YellowMouse& operator=(const YellowMouse& _Other) = delete;
	YellowMouse& operator=(YellowMouse&& _Other) noexcept = delete;

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

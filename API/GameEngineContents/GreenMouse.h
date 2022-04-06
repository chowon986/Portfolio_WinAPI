#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class GreenMouse : public Monster
{
public:
	GreenMouse();
	~GreenMouse();

	GreenMouse(const GreenMouse& _Other) = delete;
	GreenMouse(GreenMouse&& _Other) noexcept = delete;
	GreenMouse& operator=(const GreenMouse& _Other) = delete;
	GreenMouse& operator=(GreenMouse&& _Other) noexcept = delete;

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
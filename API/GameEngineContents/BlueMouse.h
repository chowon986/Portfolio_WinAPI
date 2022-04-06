#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class BlueMouse : public Monster
{
public:
	BlueMouse();
	~BlueMouse();

	BlueMouse(const BlueMouse& _Other) = delete;
	BlueMouse(BlueMouse&& _Other) noexcept = delete;
	BlueMouse& operator=(const BlueMouse& _Other) = delete;
	BlueMouse& operator=(BlueMouse&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
protected:

private:
	int HP_;
	float4 PrevPos_;
	bool CheckMapCollision();
	GameEngineImage* ColMapImage_;
	GameEngineCollision* BlueMouseCol_;
	GameEngineRenderer* BlueMouseRenderer_;
	GameEngineLevel* Level_;

private:
};
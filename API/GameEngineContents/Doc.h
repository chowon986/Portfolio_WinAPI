#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Doc : public Monster
{
public:
	Doc();
	~Doc();

	Doc(const Doc& _Other) = delete;
	Doc(Doc&& _Other) noexcept = delete;
	Doc& operator=(const Doc& _Other) = delete;
	Doc& operator=(Doc&& _Other) noexcept = delete;

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
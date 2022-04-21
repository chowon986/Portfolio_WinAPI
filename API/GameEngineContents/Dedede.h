#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel;
class Dedede : public Monster
{
public:
	Dedede();
	~Dedede();

	Dedede(const Dedede& _Other) = delete;
	Dedede(Dedede&& _Other) noexcept = delete;
	Dedede& operator=(const Dedede& _Other) = delete;
	Dedede& operator=(Dedede&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
protected:

private:
	int HP_;
	float4 PrevPos_;
	//bool CheckMapCollision();
	GameEngineImage* ColMapImage_;
	GameEngineCollision* DededeCol_;
	GameEngineRenderer* DededeRenderer_;
	GameEngineImage* DededeImage_;
	GameEngineLevel* Level_;
	

private:
};
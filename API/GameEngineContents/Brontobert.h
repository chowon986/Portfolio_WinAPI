#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class Player;
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
	void Walk() override;
protected:

private:
	float4 UpDownDir_;
};
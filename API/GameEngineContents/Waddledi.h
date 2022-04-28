#pragma once
#include "Monster.h"

class GameEngineImage;
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class Waddledi : public Monster
{
private:

public:
	Waddledi();
	~Waddledi();

	Waddledi(const Waddledi& _Other) = delete;
	Waddledi(Waddledi&& _Other) noexcept = delete;
	Waddledi& operator=(const Waddledi& _Other) = delete;
	Waddledi& operator=(Waddledi&& _Other) noexcept = delete;

public:
	void Start() override;
	void Render() override;
	void Update() override;
};
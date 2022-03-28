#pragma once
#include <GameEngine/GameEngineLevel.h>

class Cannon : public GameEngineLevel
{
public:
	Cannon();
	~Cannon();

	Cannon(const Cannon& _Other) = delete;
	Cannon(Cannon&& _Other) noexcept = delete;
	Cannon& operator=(const Cannon& _Other) = delete;
	Cannon& operator=(Cannon&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};


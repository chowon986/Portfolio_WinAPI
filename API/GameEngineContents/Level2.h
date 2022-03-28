#pragma once
#include <GameEngine/GameEngineLevel.h>

class Level2 : public GameEngineLevel
{
public:
	Level2();
	~Level2();

	Level2(const Level2& _Other) = delete;
	Level2(Level2&& _Other) noexcept = delete;
	Level2& operator=(const Level2& _Other) = delete;
	Level2& operator=(Level2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};


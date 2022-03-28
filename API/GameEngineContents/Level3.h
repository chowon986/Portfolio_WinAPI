#pragma once
#include <GameEngine/GameEngineLevel.h>

class Level3 : public GameEngineLevel
{
public:
	Level3();
	~Level3();

	Level3(const Level3& _Other) = delete;
	Level3(Level3&& _Other) noexcept = delete;
	Level3& operator=(const Level3& _Other) = delete;
	Level3& operator=(Level3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};


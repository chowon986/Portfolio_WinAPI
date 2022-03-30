#pragma once
#include <GameEngine/GameEngineLevel.h>

class Level1_2 : public GameEngineLevel
{
public:
	Level1_2();
	~Level1_2();

	Level1_2(const Level1_2& _Other) = delete;
	Level1_2(Level1_2&& _Other) noexcept = delete;
	Level1_2& operator=(const Level1_2& _Other) = delete;
	Level1_2& operator=(Level1_2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

};


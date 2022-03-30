#pragma once
#include <GameEngine/GameEngineLevel.h>

class Level1 : public GameEngineLevel
{
public:
	Level1();
	~Level1();

	Level1(const Level1& _Other) = delete;
	Level1(Level1&& _Other) noexcept = delete;
	Level1& operator=(const Level1& _Other) = delete;
	Level1& operator=(Level1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

};


#pragma once
#include <GameEngine/GameEngineLevel.h>

class Level4 : public GameEngineLevel
{
public:
	Level4();
	~Level4();

	Level4(const Level4& _Other) = delete;
	Level4(Level4&& _Other) noexcept = delete;
	Level4& operator=(const Level4& _Other) = delete;
	Level4& operator=(Level4&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

};


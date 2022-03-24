#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroLevel2 : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroLevel2();
	~IntroLevel2();

	// delete Function
	IntroLevel2(const IntroLevel2& _Other) = delete;
	IntroLevel2(IntroLevel2&& _Other) noexcept = delete;
	IntroLevel2& operator=(const IntroLevel2& _Other) = delete;
	IntroLevel2& operator=(IntroLevel2&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();

private:

};


#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroLevel0 : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroLevel0();
	~IntroLevel0();

	// delete Function
	IntroLevel0(const IntroLevel0& _Other) = delete;
	IntroLevel0(IntroLevel0&& _Other) noexcept = delete;
	IntroLevel0& operator=(const IntroLevel0& _Other) = delete;
	IntroLevel0& operator=(IntroLevel0&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();

private:

};


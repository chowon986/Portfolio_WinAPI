#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroLevel1 : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroLevel1();
	~IntroLevel1();

	// delete Function
	IntroLevel1(const IntroLevel1& _Other) = delete;
	IntroLevel1(IntroLevel1&& _Other) noexcept = delete;
	IntroLevel1& operator=(const IntroLevel1& _Other) = delete;
	IntroLevel1& operator=(IntroLevel1&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();

private:

};


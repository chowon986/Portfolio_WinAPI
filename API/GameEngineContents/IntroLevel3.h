#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroLevel3 : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroLevel3();
	~IntroLevel3();

	// delete Function
	IntroLevel3(const IntroLevel3& _Other) = delete;
	IntroLevel3(IntroLevel3&& _Other) noexcept = delete;
	IntroLevel3& operator=(const IntroLevel3& _Other) = delete;
	IntroLevel3& operator=(IntroLevel3&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();

private:

};


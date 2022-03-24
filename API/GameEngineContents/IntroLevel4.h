#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroLevel4 : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroLevel4();
	~IntroLevel4();

	// delete Function
	IntroLevel4(const IntroLevel4& _Other) = delete;
	IntroLevel4(IntroLevel4&& _Other) noexcept = delete;
	IntroLevel4& operator=(const IntroLevel4& _Other) = delete;
	IntroLevel4& operator=(IntroLevel4&& _Other) noexcept = delete;

protected:
	void Start();
	void Render();

private:

};


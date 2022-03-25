#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroBackground : public GameEngineActor
{
public:
	IntroBackground();
	~IntroBackground();

	IntroBackground(const IntroBackground& _Other) = delete;
	IntroBackground(IntroBackground&& _Other) noexcept = delete;
	IntroBackground& operator=(const IntroBackground& _Other) = delete;
	IntroBackground& operator=(IntroBackground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:


};


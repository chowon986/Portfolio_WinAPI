#pragma once
#include <GameEngine/GameEngineActor.h>

class IntroCharacter : public GameEngineActor
{
public:
	IntroCharacter();
	~IntroCharacter();

	IntroCharacter(const IntroCharacter& _Other) = delete;
	IntroCharacter(IntroCharacter&& _Other) noexcept = delete;
	IntroCharacter& operator=(const IntroCharacter& _Other) = delete;
	IntroCharacter& operator=(IntroCharacter&& _Other) noexcept = delete;

public:
	void SetImage(const std::string& _Name);

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* Renderer_;

};


#include "IntroCharacter.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

IntroCharacter::IntroCharacter()
{
	// Level_ = nullptr;
}

IntroCharacter::~IntroCharacter()
{
}

void IntroCharacter::SetImage(const std::string& _Name)
{
	Renderer_->SetImage(_Name);
}

void IntroCharacter::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()); // À§Ä¡´Â Áß¾Ó {1280, 720} {1024, 576}
}

void IntroCharacter::Update()
{

}

void IntroCharacter::Render()
{
	DebugRectRender();
}
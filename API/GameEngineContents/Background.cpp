#include "Background.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

Background::Background()
{
	// Level_ = nullptr;
}

Background::~Background()
{
}

void Background::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
}

void Background::Render()
{
	DebugRectRender();
}
#include "BotUI.h"

BotUI::BotUI()
{
}

BotUI::~BotUI()
{
}


void BotUI::Start()
{
	SetPosition({ 640, 670 });
	SetScale({ 1280, 130 });
}

void BotUI::Render()
{
	DebugRectRender();
}
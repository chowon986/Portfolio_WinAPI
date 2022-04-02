#include "BotUI.h"

BotUI::BotUI()
{
}

BotUI::~BotUI()
{
}


void BotUI::Start()
{
}

void BotUI::Render()
{
	GameEngineRenderer* PlayerUI = CreateRenderer("NormalStatus.bmp",RenderPivot::CENTER,float4(49.0f,557.0f));
	GameEngineRenderer* PlayerHP = CreateRenderer("HPUI.bmp", RenderPivot::CENTER, float4(235.0f, 550.0f));
}
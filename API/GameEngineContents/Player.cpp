#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	CreateRenderer("playerc.bmp");
	//CreateRendererToScale("BackgroundE.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
	//CreateRenderer("monster.bmp", RenderPivot::CENTER, { 0,-1000 }); // 위쪽으로 100 올려 그려라
}

void Player::Render()
{

}
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

	CreateRenderer("BackgroundE.bmp");
	//CreateRenderer("monster.bmp", RenderPivot::CENTER, { 0,-1000 }); // 위쪽으로 100 올려 그려라
}

void Player::Render()
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("BackgroundE.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("CCCCC!");
	}
	GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}
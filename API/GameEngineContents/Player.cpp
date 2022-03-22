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

	CreateRenderer("Background.bmp");


}

void Player::Render()
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Background.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("CCCCC!");
	}
	GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());
}
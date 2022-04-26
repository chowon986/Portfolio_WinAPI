#include "Level2_3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Tomato.h"

Level2_3::Level2_3()
	: Player_(nullptr)
{
}

Level2_3::~Level2_3()
{
}


void Level2_3::Loading()
{
}

void Level2_3::Update()
{
	SetCameraPos(Player_->GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 > GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}


	if (0 > GetCameraPos().y)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = 0;
		SetCameraPos(CurCameraPos);
	}

	float CameraRectX = 768;
	float CameraRectY = 576;

	if (GetMapSizeX() <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = GetCameraPos().x - (GetCameraPos().x + CameraRectX - GetMapSizeX());
		SetCameraPos(CurCameraPos);
	}

	if (GetMapSizeY() <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = GetCameraPos().y - (GetCameraPos().y + CameraRectY - GetMapSizeY());
		SetCameraPos(CurCameraPos);
	}
}

void Level2_3::LevelChangeStart()
{
	SetMapSizeX(768);
	SetMapSizeY(576);
	SetColMapImage("Stage2_3ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2_3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2_3->CreateRenderer("Stage2_3.bmp");
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(50, 320));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
	Tomato* Tomato_ = CreateActor<Tomato>((int)ORDER::ITEM);
	Tomato_->CreateRenderer("Tomato.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(384, 100));
	}
}

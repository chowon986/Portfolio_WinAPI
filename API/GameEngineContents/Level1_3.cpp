#include "Level1_3.h"
#include <GameEngine/GameEngine.h>
#include<GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "ContentsEnum.h"
#include "Background.h"
#include "BotUI.h"
#include "Player.h"
#include "Monster.h"
#include "HPUp.h"



Level1_3::Level1_3()
	: Player_(nullptr)
{
}

Level1_3::~Level1_3()
{
}


void Level1_3::Loading()
{
}

void Level1_3::Update()
{

	// CHK : CAMERA SETTING
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

void Level1_3::LevelChangeStart()
{
	SetMapSizeX(768);
	SetMapSizeY(1152);
	SetColMapImage("Stage1_3ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_3->CreateRenderer("Stage1_3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f,280.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(45, 960));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		// 아이템 생성
		HPUp* HPUp_ = CreateActor<HPUp>((int)ORDER::ITEM);
		HPUp_->SetPosition(float4(145.0f, 400.0f));
	}

	{
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorRenderer = Door->CreateRenderer("Door.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(312.0f, -36.0f));
		DoorCol1_4 = Door->CreateCollision("DoorCol1_4", float4(48.0f, 64.0f), float4(312.0f, -36.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(312.0f, -80.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}
}
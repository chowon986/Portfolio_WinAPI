#include "Level1_3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>

Level1_3::Level1_3()
	: Player_(nullptr)
	, MapSizeX_(768)
	, MapSizeY_(1152)
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

	if (MapSizeX_ <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = GetCameraPos().x - (GetCameraPos().x + CameraRectX - MapSizeX_);
		SetCameraPos(CurCameraPos);
	}

	if (MapSizeY_ <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = GetCameraPos().y - (GetCameraPos().y + CameraRectY - MapSizeY_);
		SetCameraPos(CurCameraPos);
	}
}

void Level1_3::LevelChangeStart()
{
	// 이미지 문제
	SetColMapImage("Stage1_3ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_3->CreateRenderer("Stage1_3.bmp", RenderPivot::CENTER, float4(0.0f,280.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(45, 960));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		// 아이템 생성
		Monster* HPUP = CreateActor<Monster>((int)ORDER::MONSTER);
		HPUP->CreateRenderer("HPUP.bmp", RenderPivot::CENTER, float4(145, 400));
	}

	{
		// Door 위치 조정 필요
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		DoorCol1_4 = Door->CreateCollision("DoorCol1_4", float4(48.0f, 64.0f), float4(312.0f, -36.0f));
	}
}
float Level1_3::GetMapSizeY()
{
	return MapSizeY_;
}

float Level1_3::GetMapSizeX()
{
	return MapSizeX_;
}
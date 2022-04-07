#include "Level2_2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BotUI.h"
#include "BigWaddledee.h"
#include "Waddledi.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>

Level2_2::Level2_2()
	: Player_(nullptr)
	, MapSizeX_(2214)
	, MapSizeY_(576)
{
}

Level2_2::~Level2_2()
{
}


void Level2_2::Loading()
{
}

void Level2_2::Update()
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

void Level2_2::LevelChangeStart()
{
	SetColMapImage("Stage2_2ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2_2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2_2->CreateRenderer("Stage2_2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(723.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(900, 320));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		BigWaddledee* BigWaddledee_ = CreateActor<BigWaddledee>((int)ORDER::MONSTER);
		BigWaddledee_->SetPosition(float4(700.0f, 440.0f));
	}

	{
		Waddledi* Waddledi_ = CreateActor<Waddledi>((int)ORDER::MONSTER);
		Waddledi_->SetPosition(float4(1170.0f, 393.0f));
	}

	{
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		DoorCol2_3 = Door->CreateCollision("DoorCol2_3", float4(48.0f, 64.0f), float4(1078.0f, 70.0f));
	}

}

float Level2_2::GetMapSizeY()
{
	return MapSizeY_;
}

float Level2_2::GetMapSizeX()
{
	return MapSizeX_;
}

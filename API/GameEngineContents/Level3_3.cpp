#include "Level3_3.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Waddledi.h"
#include "Monster1.h"
#include "Frosty.h"
#include "BigWaddledee.h"
#include "ContentsEnum.h"

Level3_3::Level3_3()
	: Player_(nullptr)
	, MapSizeX_(4608)
	, MapSizeY_(576)
{
}

Level3_3::~Level3_3()
{
}


void Level3_3::Loading()
{

}

void Level3_3::Update()
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

void Level3_3::LevelChangeStart()
{

	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	Waddledi* Waddledi_ = CreateActor<Waddledi>((int)ORDER::MONSTER);
	Waddledi_->SetPosition(float4(100.0f, 100.0f));

	Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
	Monster1_->SetPosition(float4(100.0f, 100.0f));

	Monster* FireItem = CreateActor<Monster1>((int)ORDER::MONSTER);
	FireItem->CreateRenderer("FireItem", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(200.0f, 200.0f));

	Frosty* Frosty_ = CreateActor<Frosty>((int)ORDER::MONSTER);
	Frosty_->SetPosition(float4(600.0f, 600.0f));

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Level3_4 = Door->CreateCollision("Level3_4", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));
}

float Level3_3::GetMapSizeX()
{
	return MapSizeX_;
}

float Level3_3::GetMapSizeY()
{
	return MapSizeY_;
}
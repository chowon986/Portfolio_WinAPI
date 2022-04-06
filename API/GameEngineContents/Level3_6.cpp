#include "Level3_6.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Doroach.h"
#include "Spinni.h"
#include "Storo.h"
#include "Doc.h"
#include "BlueMouse.h"
#include "YellowMouse.h"
#include "GreenMouse.h"
#include "Monster2.h"
#include "BigWaddledee.h"
#include "Waddledoo.h"
#include "ContentsEnum.h"

Level3_6::Level3_6()
	: Player_(nullptr)
	, MapSizeX_(4608)
	, MapSizeY_(576)
{
}

Level3_6::~Level3_6()
{
}


void Level3_6::Loading()
{

}

void Level3_6::Update()
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

void Level3_6::LevelChangeStart()
{

	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	Monster* BigTreasureChest_ = CreateActor<Monster>((int)ORDER::MONSTER);
	BigTreasureChest_->SetPosition(float4(200, 200));

	Doroach* Doroach_ = CreateActor<Doroach>((int)ORDER::MONSTER);
	Doroach_->SetPosition(float4(200.0f, 150.0f));

	Spinni* Spinni_ = CreateActor<Spinni>((int)ORDER::MONSTER);
	Spinni_->SetPosition(float4(200, 200));

	Storo* Storo_ = CreateActor<Storo>((int)ORDER::MONSTER);
	Storo_->SetPosition(float4(200.0f, 150.0f));

	Doc* Doc_ = CreateActor<Doc>((int)ORDER::MONSTER);
	Doc_->SetPosition(float4(300.0f, 300.0f));

	BlueMouse* BlueMouse_ = CreateActor<BlueMouse>((int)ORDER::MONSTER);
	BlueMouse_->SetPosition(float4(300.0f, 300.0f));

	YellowMouse* YellowMouse_ = CreateActor<YellowMouse>((int)ORDER::MONSTER);
	YellowMouse_->SetPosition(float4(300.0f, 300.0f));

	GreenMouse* GreenMouse_ = CreateActor<GreenMouse>((int)ORDER::MONSTER);
	GreenMouse_->SetPosition(float4(300.0f, 300.0f));

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Level3_7 = Door->CreateCollision("Level3_6", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));

	Monster2* Monster2_ = CreateActor<Monster2>((int)ORDER::MONSTER);
	Monster2_->SetPosition(float4(300.0f, 300.0f));

	BigWaddledee* BigWaddledee_ = CreateActor<BigWaddledee>((int)ORDER::MONSTER);
	BigWaddledee_->SetPosition(float4(300.0f, 300.0f));

	Waddledoo* Waddledoo_ = CreateActor<Waddledoo>((int)ORDER::MONSTER);
	Waddledoo_->SetPosition(float4(300.0f, 300.0f));
}

float Level3_6::GetMapSizeX()
{
	return MapSizeX_;
}

float Level3_6::GetMapSizeY()
{
	return MapSizeY_;
}
//CreateActor<BigTresureChest>((int)ORDER::MONSTER);
//CreateActor<Doc>((int)ORDER::MONSTER);
//CreateActor<Storo>((int)ORDER::MONSTER);
//CreateActor<Mice>((int)ORDER::MONSTER); // 노란 쥐 한 마리랑 storo 구현
//CreateActor<Doroach>((int)ORDER::MONSTER);
//CreateActor<Spinni>((int)ORDER::MONSTER);
//CreateActor<Doc>((int)ORDER::MONSTER);
//CreateActor<Monster2>((int)ORDER::MONSTER);
///////////////////////////
//// 동굴안
//CreateActor<Storo>((int)ORDER::MONSTER);
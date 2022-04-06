#include "Level3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Background.h"
#include "Monster.h"
#include "Monster1.h"
#include "Moon.h"
#include "Waddledi.h"
#include "BigWaddledee.h"
#include "ContentsEnum.h"

Level3::Level3()
	: Player_(nullptr)
	, MapSizeX_(4608)
	, MapSizeY_(576)
{
}

Level3::~Level3()
{
}


void Level3::Loading()
{

}

void Level3::Update()
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

void Level3::LevelChangeStart()
{

	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	Monster* Bomb1 = CreateActor<Monster>((int)ORDER::MONSTER);
	Bomb1->CreateRenderer("Bomb.bmp", RenderPivot::CENTER, float4(2140.0f, 100));

	Waddledi* Waddledi_ = CreateActor<Waddledi>((int)ORDER::MONSTER);
	Waddledi_->SetPosition(float4(100.0f, 100.0f));

	Monster* Bomb2 = CreateActor<Monster>((int)ORDER::MONSTER);
	Bomb2->CreateRenderer("Bomb.bmp", RenderPivot::CENTER, float4(2140.0f, 100));

	BigWaddledee* BigWaddledee_1 = CreateActor<BigWaddledee>((int)ORDER::MONSTER);
	BigWaddledee_1->SetPosition(float4(100.0f, 100.0f));

	Monster* Bomb3 = CreateActor<Monster>((int)ORDER::MONSTER);
	Bomb3->CreateRenderer("Bomb.bmp", RenderPivot::CENTER, float4(2140.0f, 100));

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Level3_2 = Door->CreateCollision("Level3_2", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));

	Monster* Moon_ = CreateActor<Moon>((int)ORDER::MONSTER);
	Moon_->SetPosition(float4(100.0f, 100.0f));

	Monster* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
	Monster1_->SetPosition(float4(100.0f, 100.0f));

	BigWaddledee* BigWaddledee_2 = CreateActor<BigWaddledee>((int)ORDER::MONSTER);
	BigWaddledee_2->SetPosition(float4(200.0f, 200.0f));
	GameEngineCollision* BigWaddledeeCol_2 = BigWaddledee_2->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
}

float Level3::GetMapSizeX()
{
	return MapSizeX_;
}

float Level3::GetMapSizeY()
{
	return MapSizeY_;
}
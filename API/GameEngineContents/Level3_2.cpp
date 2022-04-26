#include "Level3_2.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Waddledi.h"
#include "BigWaddledee.h"
#include "ContentsEnum.h"
#include "HPUp.h"

Level3_2::Level3_2()
	: Player_(nullptr)
{
}

Level3_2::~Level3_2()
{
}


void Level3_2::Loading()
{

}

void Level3_2::Update()
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

void Level3_2::LevelChangeStart()
{

	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	HPUp* HPUp_ = CreateActor<HPUp>((int)ORDER::MONSTER);
	HPUp_->CreateRenderer("HPUP.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(145, 400));


	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Level3_3 = Door->CreateCollision("Level3_3", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));
}
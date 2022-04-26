#include "Level3_4.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Monster3.h"
#include "BigWaddledee.h"
#include "ContentsEnum.h"

Level3_4::Level3_4()
	: Player_(nullptr)
{
}

Level3_4::~Level3_4()
{
}


void Level3_4::Loading()
{

}

void Level3_4::Update()
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

void Level3_4::LevelChangeStart()
{

	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	Monster3* Monster3_1 = CreateActor<Monster3>((int)ORDER::MONSTER);
	Monster3_1->SetPosition(float4(100.0f, 100.0f));

	Monster3* Monster3_2 = CreateActor<Monster3>((int)ORDER::MONSTER);
	Monster3_2->SetPosition(float4(100.0f, 100.0f));

	Monster3* Monster3_3 = CreateActor<Monster3>((int)ORDER::MONSTER);
	Monster3_3->SetPosition(float4(100.0f, 100.0f));

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Level3_5 = Door->CreateCollision("Level3_4", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));
}

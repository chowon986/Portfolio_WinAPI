#include "Level3_5.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BigBomb.h"
#include "Box.h"
#include "Animal.h"
#include "Waddledi.h"
#include "BigWaddledee.h"
#include "ContentsEnum.h"
#include "HPUp.h"

Level3_5::Level3_5()
	: Player_(nullptr)
{
}

Level3_5::~Level3_5()
{
}


void Level3_5::Loading()
{

}

void Level3_5::Update()
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

void Level3_5::LevelChangeStart()
{

	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}
	
	BigBomb* BigBomb_1 = CreateActor<BigBomb>((int)ORDER::MONSTER);
	BigBomb_1->SetPosition(float4(200, 200));
	
	Box* Box_1 = CreateActor<Box>((int)ORDER::MONSTER);
	Box_1->SetPosition(float4(200.0f, 150.0f));

	Box* Box_2 = CreateActor<Box>((int)ORDER::MONSTER);
	Box_2->SetPosition(float4(200.0f, 150.0f));

	BigBomb* BigBomb_2 = CreateActor<BigBomb>((int)ORDER::MONSTER);
	BigBomb_2->SetPosition(float4(200, 200));

	Box* Box_3 = CreateActor<Box>((int)ORDER::MONSTER);
	Box_3->SetPosition(float4(200.0f, 150.0f));

	Animal* Animal_1 = CreateActor<Animal>((int)ORDER::MONSTER);
	Animal_1->SetPosition(float4(300.0f, 300.0f));

	Waddledi* Waddledi_ = CreateActor<Waddledi>((int)ORDER::MONSTER);
	Waddledi_->SetPosition(float4(300.0f, 300.0f));

	HPUp* HPUp_ = CreateActor<HPUp>((int)ORDER::MONSTER);
	HPUp_->CreateRenderer("HPUP.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(600.0f, 600.0f));

	Animal* Animal_2 = CreateActor<Animal>((int)ORDER::MONSTER);
	Animal_2->SetPosition(float4(300.0f, 300.0f));

	Monster* TreasureChest = CreateActor<Monster>((int)ORDER::MONSTER);
	TreasureChest->CreateRenderer("TreasureChest.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(600.0f, 600.0f));

	BigWaddledee* BigWaddledee_ = CreateActor<BigWaddledee>((int)ORDER::MONSTER);
	BigWaddledee_->SetPosition(float4(200.0f, 150.0f));

	BigBomb* BigBomb_ = CreateActor<BigBomb>((int)ORDER::MONSTER);
	BigBomb_->SetPosition(float4(200, 200));

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Level3_6 = Door->CreateCollision("Level3_5", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));
}

#include "Level1_2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "BotUI.h"
#include "Monster.h"
#include "Waddledi.h"
#include "Box.h"
#include "Fire.h"
#include "Brontobert.h"
#include "BigBox.h"
#include "Monster1.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"

Level1_2::Level1_2()
	: Player_(nullptr)
	, MonsterRenderer_(nullptr)
{
}

Level1_2::~Level1_2()
{
}


void Level1_2::Loading()
{

}

void Level1_2::Update()
{

	//if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	//{
	//	GameEngine::GlobalEngine().ChangeLevel("Level1_3");
	//}

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

	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		//GameEngine::GlobalEngine().ChangeLevel("Level1_3");
	}
}

void Level1_2::LevelChangeStart()
{
	SetMapSizeX(4320);
	SetMapSizeY(576);

	SetColMapImage("Stage1_2ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_2->CreateRendererToScale("Stage1_2.bmp", float4(GetMapSizeX(), GetMapSizeY()), static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1776.0f, 0.0f));

	}
	{
		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);

		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(180.0f, 436.0f));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
	}
	//{
	//	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	//	Player_->SetPosition(float4(180.0f, 436.0f));
	//	PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	//}

	{
		Box* Box_1 = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box_1->SetPosition(float4(982.0f, 305.0f));
	}

	{
		Fire* Fire_ = CreateActor<Fire>((int)ORDER::MONSTER);
		Fire_->SetPosition(float4(1410.0f, 430.0f));
	}

	{
		Box* Box_2 = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box* Box_3 = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box* Box_4 = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box* Box_5 = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box* Box_6 = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box_2->SetPosition(float4(2375.0f, 270.0f));
		Box_3->SetPosition(float4(2425.0f, 270.0f));
		Box_4->SetPosition(float4(2475.0f, 270.0f));
		Box_5->SetPosition(float4(2525.0f, 270.0f));
		Box_6->SetPosition(float4(2575.0f, 270.0f));
	}

	{
		Brontobert* Brontobert_ = CreateActor<Brontobert>((int)ORDER::MONSTER);
		Brontobert_->SetPosition(float4(2980.0f, 240.0f));
		GameEngineCollision* BrontobertCol = Brontobert_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}

	{
		BigBox* BigBox_ = CreateActor<BigBox>((int)ORDER::OBSTRUCTION);
		BigBox_->SetPosition(float4(3555.0f, 380.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(3630.0f, 380.0f));
	}

	{
		Background* Grass4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass4Renderer = Grass4->CreateRenderer("grass4.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-95.0f, 147.5f));
		GameEngineImage* Grass4Image = Grass4Renderer->GetImage();
		Grass4Image->CutCount(2, 2);
		Grass4Renderer->CreateAnimation("grass4.bmp", "grass4", 0, 3, 0.5f, true);
		Grass4Renderer->ChangeAnimation("grass4");

		Background* grass5 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass5Renderer = grass5->CreateRenderer("grass5.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1297.0f, 147.0f));
		GameEngineImage* Grass5Image = Grass5Renderer->GetImage();
		Grass5Image->CutCount(2, 2);
		Grass5Renderer->CreateAnimation("grass5.bmp", "grass5", 0, 3, 0.5f, true);
		Grass5Renderer->ChangeAnimation("grass5");

		Background* grass6 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass6Renderer = grass6->CreateRenderer("grass6.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(2880.0f, 147.0f));
		GameEngineImage* Grass6Image = Grass6Renderer->GetImage();
		Grass6Image->CutCount(2, 2);
		Grass6Renderer->CreateAnimation("grass6.bmp", "grass6", 0, 3, 0.5f, true);
		Grass6Renderer->ChangeAnimation("grass6");

		Background* grass7 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass7Renderer = grass7->CreateRenderer("grass7.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(3841.0f, 53.0f));
		GameEngineImage* Grass7Image = Grass7Renderer->GetImage();
		Grass7Image->CutCount(2, 2);
		Grass7Renderer->CreateAnimation("grass7.bmp", "grass7", 0, 3, 0.5f, true);
		Grass7Renderer->ChangeAnimation("grass7");
	}

	{
		// Door
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorRenderer = Door->CreateRenderer("Door.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(3870.0f, 10.0f));
		DoorCol1_3 = Door->CreateCollision("DoorCol1_3", float4(44.0f, 64.0f), float4(3870.0f, 20.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(3870.0f, -20.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}
}

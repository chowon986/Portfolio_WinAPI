#include "Level1_2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "BotUI.h"
#include "Monster.h"
////#include "Waddledi.h"
//#include "Waddledu.h"
//#include "Sparky.h"
//#include "Box.h"
//#include "Fire.h"
//#include "Brontobert.h"
//#include "BigBox.h"
//#include "Monster1.h"
//#include "Tomato.h"
//#include "Bomb.h"
//#include "Background.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>

Level1_2::Level1_2()
	: MapSizeX_(4320)
	, MapSizeY_(576)
	, Player_(nullptr)
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
	/*if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_3");
	}*/

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

	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Level1_3");
	}
}

void Level1_2::LevelChangeStart()
{

	{
		Background* Stage1_2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_2->CreateRendererToScale("Stage1_2.bmp", float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(1776.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	{
		Monster* Box = CreateActor<Monster>((int)ORDER::MONSTER);
		Box->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(982.0f, 305.0f));

	}

	{
		Monster* Fire = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* FireRenderer = Fire->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(1400.0f, 440.0f));
		GameEngineImage* FireImage = FireRenderer->GetImage();
		FireImage->CutCount(10, 26);
		FireRenderer->CreateAnimation("monster0.bmp", "FireIdel", 160, 164, 0.3f, true);
		FireRenderer->ChangeAnimation("FireIdel");
	}

	{
		Monster* Box1 = CreateActor<Monster>((int)ORDER::MONSTER);
		Monster* Box2 = CreateActor<Monster>((int)ORDER::MONSTER);
		Monster* Box3 = CreateActor<Monster>((int)ORDER::MONSTER);
		Monster* Box4 = CreateActor<Monster>((int)ORDER::MONSTER);
		Monster* Box5 = CreateActor<Monster>((int)ORDER::MONSTER);
		Box1->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(2375.0f, 270.0f));
		Box2->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(2425.0f, 270.0f));
		Box3->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(2475.0f, 270.0f));
		Box4->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(2525.0f, 270.0f));
		Box5->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(2575.0f, 270.0f));
	}

	{
		Monster* Brontobert = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* BrontobertRenderer = Brontobert->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(2980.0f, 240.0f));
		GameEngineImage* BrontobertImage = BrontobertRenderer->GetImage();
		BrontobertImage->CutCount(10, 26);
		BrontobertRenderer->CreateAnimation("monster0.bmp", "BrontobertIdel", 33, 34, 0.3f, true);
		BrontobertRenderer->ChangeAnimation("BrontobertIdel");
	}

	{
		Monster* BigBox = CreateActor<Monster>((int)ORDER::MONSTER);
		BigBox->CreateRenderer("BigBox.bmp", RenderPivot::CENTER, float4(3555.0f, 380.0f));
	}

	{
		Monster* Monster1 = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* Monster1Renderer = Monster1->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(3630.0f, 420.0f));
		GameEngineImage* Monster1Image = Monster1Renderer->GetImage();
		Monster1Image->CutCount(10, 26);
		Monster1Renderer->CreateAnimation("monster0.bmp", "Monster1Idel", 216, 219, 0.3f, true);
		Monster1Renderer->ChangeAnimation("Monster1Idel");
	}

	{
		Background* Grass4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass4Renderer = Grass4->CreateRenderer("grass4.bmp", RenderPivot::CENTER, float4(-95.0f, 147.0f));
		GameEngineImage* Grass4Image = Grass4Renderer->GetImage();
		Grass4Image->CutCount(2, 2);
		Grass4Renderer->CreateAnimation("grass4.bmp", "grass4", 0, 3, 0.5f, true);
		Grass4Renderer->ChangeAnimation("grass4");
	}

	{
		Background* grass5 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass5Renderer = grass5->CreateRenderer("grass5.bmp", RenderPivot::CENTER, float4(1300.0f, 147.0f));
		GameEngineImage* Grass5Image = Grass5Renderer->GetImage();
		Grass5Image->CutCount(2, 2);
		Grass5Renderer->CreateAnimation("grass5.bmp", "grass5", 0, 3, 0.5f, true);
		Grass5Renderer->ChangeAnimation("grass5");
	}

	{
		Background* grass6 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass6Renderer = grass6->CreateRenderer("grass6.bmp", RenderPivot::CENTER, float4(2880.0f, 147.0f));
		GameEngineImage* Grass6Image = Grass6Renderer->GetImage();
		Grass6Image->CutCount(2, 2);
		Grass6Renderer->CreateAnimation("grass6.bmp", "grass6", 0, 3, 0.5f, true);
		Grass6Renderer->ChangeAnimation("grass6");
	}

	{
		// CHK : CAMERA SET
		Background* grass7 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass7Renderer = grass7->CreateRenderer("grass7.bmp", RenderPivot::CENTER, float4(3841.0f, 53.0f));
		GameEngineImage* Grass7Image = Grass7Renderer->GetImage();
		Grass7Image->CutCount(2, 2);
		Grass7Renderer->CreateAnimation("grass7.bmp", "grass7", 0, 3, 0.5f, true);
		Grass7Renderer->ChangeAnimation("grass7");
	}
}

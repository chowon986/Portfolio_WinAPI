#include "Level2_2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BotUI.h"
#include "BigWaddledee.h"
#include "Waddledee.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"
#include "AbandonEffect.h"
#include <GameEngine/GameEngineImage.h>
#include "TransformEffect.h"


Level2_2::Level2_2()
	: Player_(nullptr)

{
}

Level2_2::~Level2_2()
{
}


void Level2_2::Loading()
{
}

void Level2_2::DelayUpdate()
{
	SetCameraPos(Player_->GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 >= GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}

	if (0 >= GetCameraPos().y)
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
		CurCameraPos.x = static_cast<int>(GetCameraPos().ix() - (GetCameraPos().ix() + CameraRectX - GetMapSizeX()));
		SetCameraPos(CurCameraPos);
	}

	if (GetMapSizeY() <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = static_cast<int>(GetCameraPos().iy() - (GetCameraPos().iy() + CameraRectY - GetMapSizeY()));
		SetCameraPos(CurCameraPos);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Collision"))
	{
		IsDebugModeOn();
	}
}

void Level2_2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	SetMapSizeX(2214);
	SetMapSizeY(576);
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
		Player_->SetPosition(float4(200, 380));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);

		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		TransformEffect* TransformEffect_ = CreateActor<TransformEffect>((int)ORDER::EFFECT);
		Player_->SetTransformEffect(TransformEffect_);
		Player_->SetAbandonEffect(AbandonEffect_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}
	{
		Background* Grass8 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass8Renderer = Grass8->CreateRenderer("grass8.bmp");
		GameEngineImage* Grass8Image = Grass8Renderer->GetImage();
		Grass8Image->CutCount(4, 1);
		Grass8Renderer->CreateAnimation("grass8.bmp", "grass8", 0, 3, 0.5f, true);
		Grass8Renderer->ChangeAnimation("grass8");
		Grass8Renderer->SetPivot(float4(-48.0f, 102.0f));

		Background* Grass9 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass9Renderer = Grass9->CreateRenderer("Grass9.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(480.0f, 150.0f));
		GameEngineImage* Grass9Image = Grass9Renderer->GetImage();
		Grass9Image->CutCount(4, 1);
		Grass9Renderer->CreateAnimation("Grass9.bmp", "Grass9", 0, 3, 0.5f, true);
		Grass9Renderer->ChangeAnimation("Grass9");

		Background* Grass10 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass10Renderer = Grass10->CreateRenderer("Grass10.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(936.0f, 102.0f));
		GameEngineImage* Grass10Image = Grass10Renderer->GetImage();
		Grass10Image->CutCount(4, 1);
		Grass10Renderer->CreateAnimation("Grass10.bmp", "Grass10", 0, 3, 0.5f, true);
		Grass10Renderer->ChangeAnimation("Grass10");

		Background* Grass11 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass11Renderer = Grass11->CreateRenderer("Grass11.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1452.0f, 102.0f));
		GameEngineImage* Grass11Image = Grass11Renderer->GetImage();
		Grass11Image->CutCount(4, 1);
		Grass11Renderer->CreateAnimation("Grass11.bmp", "Grass11", 0, 3, 0.5f, true);
		Grass11Renderer->ChangeAnimation("Grass11");
	}

	{ 
		// Door
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorRenderer = Door->CreateRenderer("Door.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1705.0f, 70.0f));
		DoorCol2_3 = Door->CreateCollision("DoorCol2_3", float4(48.0f, 64.0f), float4(1705.0f, 70.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1705, 25.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}

	{
		BigWaddledee* BigWaddledee_ = CreateActor<BigWaddledee>((int)ORDER::MONSTER);
		BigWaddledee_->SetPosition(float4(700.0f, 440.0f));
	}

	{
		Waddledee* Waddledee_ = CreateActor<Waddledee>((int)ORDER::MONSTER);
		Waddledee_->SetPosition(float4(1170.0f, 393.0f));
	}

}

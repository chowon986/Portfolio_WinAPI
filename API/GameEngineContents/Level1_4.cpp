#include "Level1_4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster1.h"
#include "Fire.h"
#include "Waddledee.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include "Tomato.h"
#include "Box.h"
#include "BombBox.h"
#include "Bomb.h"
#include "BotUI.h"
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"
#include "AbandonEffect.h"
#include "Ground.h"
#include "GameEngineBase/GameEngineSound.h"
#include "Animal.h"
#include "BombBomb.h"

Level1_4::Level1_4()
	: Player_(nullptr)
	, PlayerStatus_(nullptr)
	, Cannon_(nullptr)
{
}

Level1_4::~Level1_4()
{
}


void Level1_4::Loading()
{
}

void Level1_4::DelayUpdate()
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

void Level1_4::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	LEVEL_BGM.Stop();
}

void Level1_4::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	GameEngineLevelBase::MAJOR_LEVEL = 1;
	SetMapSizeX(4608);
	SetMapSizeY(576);
	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_4->CreateRendererToScale("Stage1_4.bmp", float4(GetMapSizeX(), GetMapSizeY()), static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(205.0f, 430.0f));
		Player_->SetMapStartPos(float4(205.0f, 430.0f));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);

		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		Player_->SetAbandonEffect(AbandonEffect_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}

	{
		Box* Box_ = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box_->SetPosition(float4(890.0f, 350.0f));
	}

	{
		Fire* Fire_ = CreateActor<Fire>((int)ORDER::MONSTER);
		Fire_->SetPosition(float4(950.0f, 380.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(1500.0f, 380.0f));
	}

	{
		Tomato* Tomato_ = CreateActor<Tomato>((int)ORDER::ITEM);
		Tomato_->SetPosition(float4(2140.0f, 400.0f));
	}

	{
		Animal* Animal_ = CreateActor<Animal>((int)ORDER::MONSTER);
		Animal_->SetPosition(float4(1750.0f, 290.0f));
	}

	{
		Ground* Ground0 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground0->GetRenderer()->ChangeAnimation("0");
		Ground0->SetPosition(float4(1853.0f, 283.0f));

		Ground* Ground1 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground1->GetRenderer()->ChangeAnimation("1");
		Ground1->SetPosition(float4(1916.0f, 283.0f));

		Ground* Ground2 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground2->GetRenderer()->ChangeAnimation("2");
		Ground2->SetPosition(float4(1979.0f, 283.0f));

		Ground* Ground3 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground3->GetRenderer()->ChangeAnimation("3");
		Ground3->SetPosition(float4(2042.0f, 283.0f));

		Ground* Ground4 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground4->GetRenderer()->ChangeAnimation("4");
		Ground4->SetPosition(float4(2105.0f, 283.0f));

		Ground* Ground5 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground5->GetRenderer()->ChangeAnimation("5");
		Ground5->SetPosition(float4(2168.0f, 283.0f));

		Ground* Ground6 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground6->GetRenderer()->ChangeAnimation("6");
		Ground6->SetPosition(float4(2231.0f, 283.0f));

		Ground* Ground7 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground7->GetRenderer()->ChangeAnimation("7");
		Ground7->SetPosition(float4(2294.0f, 283.0f));

		Ground* Ground8 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground8->GetRenderer()->ChangeAnimation("8");
		Ground8->SetPosition(float4(2357.0f, 283.0f));

		Ground* Ground9 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground9->GetRenderer()->ChangeAnimation("9");
		Ground9->SetPosition(float4(2420.0f, 283.0f));

		Ground* Ground10 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground10->GetRenderer()->ChangeAnimation("10");
		Ground10->SetPosition(float4(1853.0f, 325.0f));

		Ground* Ground11 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground11->GetRenderer()->ChangeAnimation("11");
		Ground11->SetPosition(float4(1916.0f, 325.0f));

		Ground* Ground12 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground12->GetRenderer()->ChangeAnimation("12");
		Ground12->SetPosition(float4(1979.0f, 325.0f));

		Ground* Ground13 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground13->GetRenderer()->ChangeAnimation("13");
		Ground13->SetPosition(float4(2042.0f, 325.0f));

		Ground* Ground14 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground14->GetRenderer()->ChangeAnimation("14");
		Ground14->SetPosition(float4(2105.0f, 325.0f));

		Ground* Ground15 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground15->GetRenderer()->ChangeAnimation("15");
		Ground15->SetPosition(float4(2168.0f, 325.0f));

		Ground* Ground16 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground16->GetRenderer()->ChangeAnimation("16");
		Ground16->SetPosition(float4(2231.0f, 325.0f));

		Ground* Ground17 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground17->GetRenderer()->ChangeAnimation("17");
		Ground17->SetPosition(float4(2294.0f, 325.0f));

		Ground* Ground18 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground18->GetRenderer()->ChangeAnimation("18");
		Ground18->SetPosition(float4(2357.0f, 325.0f));

		Ground* Ground19 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground19->GetRenderer()->ChangeAnimation("19");
		Ground19->SetPosition(float4(2420.0f, 325.0f));

		Ground* Ground20 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground20->GetRenderer()->ChangeAnimation("20");
		Ground20->SetPosition(float4(1853.0f, 367.0f));

		Ground* Ground21 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground21->GetRenderer()->ChangeAnimation("21");
		Ground21->SetPosition(float4(1916.0f, 367.0f));

		Ground* Ground22 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground22->GetRenderer()->ChangeAnimation("22");
		Ground22->SetPosition(float4(1979.0f, 367.0f));

		Ground* Ground23 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground23->GetRenderer()->ChangeAnimation("23");
		Ground23->SetPosition(float4(2042.0f, 367.0f));

		Ground* Ground24 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground24->GetRenderer()->ChangeAnimation("24");
		Ground24->SetPosition(float4(2105.0f, 367.0f));

		Ground* Ground25 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground25->GetRenderer()->ChangeAnimation("25");
		Ground25->SetPosition(float4(2168.0f, 367.0f));

		Ground* Ground26 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground26->GetRenderer()->ChangeAnimation("26");
		Ground26->SetPosition(float4(2231.0f, 367.0f));

		Ground* Ground27 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground27->GetRenderer()->ChangeAnimation("27");
		Ground27->SetPosition(float4(2294.0f, 367.0f));

		Ground* Ground28 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground28->GetRenderer()->ChangeAnimation("28");
		Ground28->SetPosition(float4(2357.0f, 367.0f));

		Ground* Ground29 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground29->GetRenderer()->ChangeAnimation("29");
		Ground29->SetPosition(float4(2420.0f, 367.0f));

		Ground* Ground30 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground30->GetRenderer()->ChangeAnimation("30");
		Ground30->SetPosition(float4(1852.0f, 409.0f));

		Ground* Ground31 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground31->GetRenderer()->ChangeAnimation("31");
		Ground31->SetPosition(float4(1915.0f, 409.0f));

		Ground* Ground32 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground32->GetRenderer()->ChangeAnimation("32");
		Ground32->SetPosition(float4(1978.0f, 409.0f));

		Ground* Ground33 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground33->GetRenderer()->ChangeAnimation("33");
		Ground33->SetPosition(float4(2041.0f, 409.0f));

		Ground* Ground34 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground34->GetRenderer()->ChangeAnimation("34");
		Ground34->SetPosition(float4(2104.0f, 409.0f));

		Ground* Ground35 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground35->GetRenderer()->ChangeAnimation("35");
		Ground35->SetPosition(float4(2167.0f, 409.0f));

		Ground* Ground36 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground36->GetRenderer()->ChangeAnimation("36");
		Ground36->SetPosition(float4(2230.0f, 409.0f));

		Ground* Ground37 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground37->GetRenderer()->ChangeAnimation("37");
		Ground37->SetPosition(float4(2293.0f, 409.0f));

		Ground* Ground38 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground38->GetRenderer()->ChangeAnimation("38");
		Ground38->SetPosition(float4(2356.0f, 409.0f));

		Ground* Ground39 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground39->GetRenderer()->ChangeAnimation("39");
		Ground39->SetPosition(float4(2419.0f, 409.0f));

		Ground* Ground40 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground40->GetRenderer()->ChangeAnimation("40");
		Ground40->SetPosition(float4(1850.0f, 451.0f));

		Ground* Ground41 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground41->GetRenderer()->ChangeAnimation("41");
		Ground41->SetPosition(float4(1913.0f, 451.0f));

		Ground* Ground42 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground42->GetRenderer()->ChangeAnimation("42");
		Ground42->SetPosition(float4(1976.0f, 451.0f));

		Ground* Ground43 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground43->GetRenderer()->ChangeAnimation("43");
		Ground43->SetPosition(float4(2039.0f, 451.0f));

		Ground* Ground44 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground44->GetRenderer()->ChangeAnimation("44");
		Ground44->SetPosition(float4(2102.0f, 451.0f));

		Ground* Ground45 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground45->GetRenderer()->ChangeAnimation("45");
		Ground45->SetPosition(float4(2165.0f, 451.0f));

		Ground* Ground46 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground46->GetRenderer()->ChangeAnimation("46");
		Ground46->SetPosition(float4(2228.0f, 451.0f));

		Ground* Ground47 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground47->GetRenderer()->ChangeAnimation("47");
		Ground47->SetPosition(float4(2291.0f, 451.0f));

		Ground* Ground48 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground48->GetRenderer()->ChangeAnimation("48");
		Ground48->SetPosition(float4(2354.0f, 451.0f));

		Ground* Ground49 = CreateActor<Ground>((int)ORDER::OBSTRUCTION);
		Ground49->GetRenderer()->ChangeAnimation("49");
		Ground49->SetPosition(float4(2417.0f, 451.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(3300.0f, 480.0f));
	}

	{
		BombBomb* BombBomb_ = CreateActor<BombBomb>((int)ORDER::OBSTRUCTION);
		BombBomb_->SetPosition(float4(4200.0f, -5.0f));
	}
	//{
	//	Bomb* Bomb_ = CreateActor<Bomb>((int)ORDER::OBSTRUCTION);
	//	Bomb_->SetPosition(float4(3920.0f, 210.0f));
	//}


	//{
	//	BombBox* BombBox1 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox1->SetPosition(float4(3965.0f, 210.0f));
	//	BombBox* BombBox2 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox2->SetPosition(float4(4010.0f, 210.0f));
	//	BombBox* BombBox3 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox3->SetPosition(float4(4055.0f, 210.0f));
	//	BombBox* BombBox4 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox4->SetPosition(float4(4100.0f, 210.0f));
	//	BombBox* BombBox5 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox5->SetPosition(float4(4145.0f, 210.0f));
	//	BombBox* BombBox6 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox6->SetPosition(float4(3965.0f, 165.0f));
	//	BombBox* BombBox7 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox7->SetPosition(float4(4010.0f, 165.0f));
	//	BombBox* BombBox8 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox8->SetPosition(float4(4055.0f, 165.0f));
	//	BombBox* BombBox9 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox9->SetPosition(float4(4100.0f, 165.0f));
	//	BombBox* BombBox10 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox10->SetPosition(float4(4145.0f, 165.0f));
	//	BombBox* BombBox11 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox11->SetPosition(float4(3965.0f, 120.0f));
	//	BombBox* BombBox12 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox12->SetPosition(float4(4010.0f, 120.0f));
	//	BombBox* BombBox13 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox13->SetPosition(float4(4055.0f, 120.0f));
	//	BombBox* BombBox14 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox14->SetPosition(float4(4100.0f, 120.0f));
	//	BombBox* BombBox15 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox15->SetPosition(float4(4145.0f, 120.0f));
	//	BombBox* BombBox16 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox16->SetPosition(float4(3965.0f, 75.0f));
	//	BombBox* BombBox17 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox17->SetPosition(float4(4010.0f, 75.0f));
	//	BombBox* BombBox18 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox18->SetPosition(float4(4055.0f, 75.0f));
	//	BombBox* BombBox19 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox19->SetPosition(float4(4100.0f, 75.0f));
	//	BombBox* BombBox20 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox20->SetPosition(float4(4145.0f, 75.0f));
	//	BombBox* BombBox21 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox21->SetPosition(float4(3965.0f, 30.0f));
	//	BombBox* BombBox22 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox22->SetPosition(float4(4010.0f, 30.0f));
	//	BombBox* BombBox23 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox23->SetPosition(float4(4055.0f, 30.0f));
	//	BombBox* BombBox24 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox24->SetPosition(float4(4100.0f, 30.0f));
	//	BombBox* BombBox25 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
	//	BombBox25->SetPosition(float4(4145.0f, 30.0f));
	//}

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* DoorRenderer = Door->CreateRenderer("BigDoor.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4120.0f, -117.0f));
	Cannon_ = Door->CreateCollision("Cannon", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));

	Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("BigDoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4120.0f, -140.0f));
	GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
	DoorStarImage->CutCount(6, 2);
	DoorStarRenderer->CreateAnimation("BigDoorStar.bmp", "BigDoorStar", 0, 11, 0.05f, true);
	DoorStarRenderer->ChangeAnimation("BigDoorStar");
}

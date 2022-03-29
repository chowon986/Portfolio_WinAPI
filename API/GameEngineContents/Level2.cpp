#include "Level2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "SwordItem.h"
#include "Waddledi.h"
#include "Tomato.h"
#include "Sword.h"
#include "TreasureChest.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Tiktik.h"
#include "Background.h"
#include "ContentsEnum.h"

Level2::Level2()
{
}

Level2::~Level2()
{
}


void Level2::Loading()
{
	//Ä¿ºñ
	CreateActor<SwordItem>((int)ORDER::MONSTER);
	CreateActor<Waddledi>((int)ORDER::MONSTER);
	///////////////////////////
	CreateActor<Tomato>((int)ORDER::MONSTER);
	///////////////////
	CreateActor<Sword>((int)ORDER::MONSTER);
	CreateActor<TreasureChest>((int)ORDER::MONSTER);
	CreateActor<Monster1>((int)ORDER::MONSTER);
	CreateActor<Monster1>((int)ORDER::MONSTER); // cut
	CreateActor<Monster2>((int)ORDER::MONSTER);
	CreateActor<Tiktik>((int)ORDER::MONSTER);
}

void Level2::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Cannon");
	}
}
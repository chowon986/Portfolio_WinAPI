#include "Level3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Bomb.h"
#include "BigWaddledi.h"
#include "HPUp.h"
#include "Moon.h"
#include "Monster1.h"
#include "Waddledi.h"
#include "FireItem.h"
#include "Frosty.h"
#include "Fire.h"
#include "BigBomb.h"
#include "Box.h"
#include "Animal.h"
#include "TreasureChest.h"
#include "BigTresureChest.h"
#include "Doc.h"
#include "Storo.h"
#include "Mice.h"
#include "Doroach.h"
#include "Spinni.h"
#include "Monster2.h"
#include "Background.h"
#include "ContentsEnum.h"

Level3::Level3()
{
}

Level3::~Level3()
{
}


void Level3::Loading()
{
	//kirby
	CreateActor<Bomb>((int)ORDER::MONSTER);
	CreateActor<Bomb>((int)ORDER::MONSTER);
	CreateActor<BigWaddledi>((int)ORDER::MONSTER);
	/////////////////////////
	CreateActor<HPUp>((int)ORDER::MONSTER);
	/////////////////////////
	CreateActor<Moon>((int)ORDER::MONSTER);
	CreateActor<Monster1>((int)ORDER::MONSTER);
	CreateActor<BigWaddledi>((int)ORDER::MONSTER);
	///////////////////////
	CreateActor<Waddledi>((int)ORDER::MONSTER);
	CreateActor<Monster1>((int)ORDER::MONSTER);
	CreateActor<FireItem>((int)ORDER::MONSTER);
	CreateActor<Frosty>((int)ORDER::MONSTER);
	//////////////////////
	CreateActor<Fire>((int)ORDER::MONSTER); // ÃÑ 3¸¶¸®
	CreateActor<BigBomb>((int)ORDER::MONSTER);
	CreateActor<Box>((int)ORDER::MONSTER); // 2°³
	CreateActor<BigBomb>((int)ORDER::MONSTER);
	CreateActor<Box>((int)ORDER::MONSTER); // 1°³
	CreateActor<Animal>((int)ORDER::MONSTER);
	CreateActor<Waddledi>((int)ORDER::MONSTER);
	CreateActor<HPUp>((int)ORDER::MONSTER);
	CreateActor<Animal>((int)ORDER::MONSTER);
	CreateActor<TreasureChest>((int)ORDER::MONSTER);
	CreateActor<BigBomb>((int)ORDER::MONSTER);
	CreateActor<BigWaddledi>((int)ORDER::MONSTER);
	//////////////////////////
	CreateActor<BigTresureChest>((int)ORDER::MONSTER);
	CreateActor<Doc>((int)ORDER::MONSTER);
	CreateActor<Storo>((int)ORDER::MONSTER);
	CreateActor<Mice>((int)ORDER::MONSTER); // ³ë¶õ Áã ÇÑ ¸¶¸®¶û storo ±¸Çö
	CreateActor<Doroach>((int)ORDER::MONSTER);
	CreateActor<Spinni>((int)ORDER::MONSTER);
	CreateActor<Doc>((int)ORDER::MONSTER);
	CreateActor<Monster2>((int)ORDER::MONSTER);
	/////////////////////////
	// µ¿±¼¾È
	CreateActor<Storo>((int)ORDER::MONSTER);


}

void Level3::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Cannon");
	}
}
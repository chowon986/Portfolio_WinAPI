#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "IntroLevel0.h"
#include "IntroLevel1.h"
#include "IntroLevel2.h"
#include "IntroLevel3.h"
#include "IntroLevel4.h"



TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	CreateActor<IntroLevel0>("IntroLevel0", 0);
	CreateActor<IntroLevel1>("IntroLevel1", 1);
	CreateActor<IntroLevel2>("IntroLevel1", 2);
	CreateActor<IntroLevel3>("IntroLevel1", 3);
	CreateActor<IntroLevel4>("IntroLevel1", 4);
}

void TitleLevel::LevelChangeStart()
{

}

void TitleLevel::Update()
{
	// GameEngine::GlobalEngine().ChangeLevel("Play");
}
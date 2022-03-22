#include "Kirby.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	// 리소스를 다 로드하지 못하는 상황이 올수가 없다.

	GameEngineImageManager::GetInst()->Load("C:\\Background.bmp", "Background.bmp");


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void Kirby::GameLoop()
{

}
void Kirby::GameEnd()
{

}
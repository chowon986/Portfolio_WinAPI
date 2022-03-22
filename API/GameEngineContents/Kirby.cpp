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

	// ���ҽ��� �� �ε����� ���ϴ� ��Ȳ�� �ü��� ����.

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
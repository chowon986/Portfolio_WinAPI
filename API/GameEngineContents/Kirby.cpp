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

	GameEngineImageManager::GetInst()->Load("D:\\Project\\AR33\\API\\Project\\ApiFrameWork\\Res\\Texture\\Idle.bmp", "Idle.bmp");


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
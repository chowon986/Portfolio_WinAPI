#include "EndingStory.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineInput.h>

EndingStory::EndingStory()
{
}

EndingStory::~EndingStory()
{
}

void EndingStory::Loading()
{
}

// void EndingStory::LevelChangeStart()
//CreateActor<EndingBackground>((int)ORDER::BACKGROUND, "Ending"); // ���� ���丮 �߰�


void EndingStory::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Ending");
	}
}
#include "EndingStoryLevel.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineInput.h>

enum class ORDER
{
	BACKGROUND,
};

EndingStoryLevel::EndingStoryLevel()
{
}

EndingStoryLevel::~EndingStoryLevel()
{
}

void EndingStoryLevel::Loading()
{
}

void EndingStoryLevel::LevelChangeStart()
{
	//CreateActor<EndingBackground>((int)ORDER::BACKGROUND, "Ending"); // 엔딩 스토리 추가

}

void EndingStoryLevel::Update()
{

	//GameEngine::GlobalEngine().ChangeLevel("Story");
}
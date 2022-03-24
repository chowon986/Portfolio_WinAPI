#include "GameEngineActor.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
{
	// delete this;
}

GameEngineActor::~GameEngineActor()
{
	std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
	std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		delete (*StartIter);
		(*StartIter) = nullptr;
	}
}

void GameEngineActor::DebugRectRender()
{
	// 선생님은 기본적으로 중앙을 기준으로하는걸 좋아합니다.

	GameEngineRect DebugRect(Position_, Scale_);


	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image,
	RenderPivot _PivotType /*= RenderPivot::CENTER*/,
	const float4& _PivotPos /*= { 0,0 }*/
)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();
	
	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);
	
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale(const std::string& _Image, const float4& Scale, RenderPivot _PivotType, const float4& _PivotPos)
{
	// HP 바 처럼 크기 조절이 필요한 경우 사용
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetImageScale();
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

void GameEngineActor::Renderering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}

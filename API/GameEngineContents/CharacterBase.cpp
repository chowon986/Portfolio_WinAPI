#include "CharacterBase.h"
#include <GameEngine/GameEngine.h>

CharacterBase::CharacterBase()
	: HP_(0)
	, Speed_(200)
	//, State_(CharacterState::IDLE) // enum class 사용 방법
	, JumpMaxHeight_(10)
	, JumpHeight_(50)
	, JumpDirection_({0, 0})
	, DelayTime_(0.0f)
	, ElapsedTime_(0.0f)
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Update()
{
	ElapsedTime_ += GameEngineTime::GetDeltaTime();
	if (ElapsedTime_ > DelayTime_)
	{
		DelayUpdate();
	}
}

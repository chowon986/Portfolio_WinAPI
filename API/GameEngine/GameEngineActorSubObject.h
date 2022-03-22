#pragma once
#include <GameEngine/GameEngineActor.h>

// 엑터가 먼저 -> 랜더러가 그 다음

class GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	//생성자, 소멸자, 복사 생성자, Rvalue 복사 생성자, 대입 연산자, Rvalue 대입 연산자
	GameEngineActorSubObject();
	~GameEngineActorSubObject();

	GameEngineActorSubObject(const GameEngineActorSubObject& _other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _other) = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _other) noexcept = delete;

	inline GameEngineActor* GetActor()
	{
		return Actor_;
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}

private:
	GameEngineActor* Actor_;
};


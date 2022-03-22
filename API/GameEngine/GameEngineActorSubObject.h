#pragma once
#include <GameEngine/GameEngineActor.h>

// ���Ͱ� ���� -> �������� �� ����

class GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	//������, �Ҹ���, ���� ������, Rvalue ���� ������, ���� ������, Rvalue ���� ������
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


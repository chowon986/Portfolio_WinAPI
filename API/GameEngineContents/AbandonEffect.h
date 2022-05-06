#pragma once
#include <GameEngine/GameEngineActor.h>


enum class AbandonEffectState
{
	Left,
	Right,
	Eaten,
	None,
};

enum class MonsterClass;

class GameEngineImage;
class AbandonEffect : public GameEngineActor
{
public:
	AbandonEffect();
	~AbandonEffect();

	AbandonEffect(const AbandonEffect& _Other) = delete;
	AbandonEffect(AbandonEffect&& _Other) noexcept = delete;
	AbandonEffect& operator=(const AbandonEffect& _Other) = delete;
	AbandonEffect& operator=(AbandonEffect&& _Other) noexcept = delete;

public:
	void SetState(AbandonEffectState _AbandonEffectState);
	AbandonEffectState GetState();

	void SetMonsterClass(MonsterClass _MonsterClass) { MonsterClass_ = _MonsterClass; }
	MonsterClass GetMonsterClass() { return MonsterClass_; }
private:
	void StateUpdate();
	void UpdateAbandonEffectRight();
	void UpdateAbandonEffectLeft();
	void UpdateEaten();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	MonsterClass MonsterClass_;
	AbandonEffectState AbandonEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineImage* Image_;
	float Time_;
};
#pragma once
#include <GameEngine/GameEngineActor.h>

enum class SwordAttackEffectState
{
	SwordAttackEffect,
	SwordJumpAttackEffect,
	None
};

class SwordAttackEffect : public GameEngineActor
{
public:
	SwordAttackEffect();
	~SwordAttackEffect();

	SwordAttackEffect(const SwordAttackEffect& _Other) = delete;
	SwordAttackEffect(SwordAttackEffect&& _Other) noexcept = delete;
	SwordAttackEffect& operator=(const SwordAttackEffect& _Other) = delete;
	SwordAttackEffect& operator=(SwordAttackEffect&& _Other) noexcept = delete;

public:
	void SetState(SwordAttackEffectState _SwordAttackEffectState);
	SwordAttackEffectState GetState();
private:
	void StateUpdate();
	void UpdateSwordAttackEffect();
	void UpdateSwordJumpAttackEffect();

	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	SwordAttackEffectState SwordAttackEffectState_;
	SwordAttackEffectState SwordJumpAttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* SwordEffectCollision_;
	GameEngineImage* Image_;
};
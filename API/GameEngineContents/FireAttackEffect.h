#pragma once
#include <GameEngine/GameEngineActor.h>

enum class FireAttackEffectState
{
	FireAttackEffectRight,
	FireAttackEffectLeft,
	None,
};

class FireAttackEffect : public GameEngineActor
{
public:
	FireAttackEffect();
	~FireAttackEffect();

	FireAttackEffect(const FireAttackEffect& _Other) = delete;
	FireAttackEffect(FireAttackEffect&& _Other) noexcept = delete;
	FireAttackEffect& operator=(const FireAttackEffect& _Other) = delete;
	FireAttackEffect& operator=(FireAttackEffect&& _Other) noexcept = delete;

public:
	void SetState(FireAttackEffectState _FireAttackEffectState);
	FireAttackEffectState GetState();
private:
	void StateUpdate();
	void UpdateFireAttackEffectRight();
	void UpdateFireAttackEffectLeft();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	FireAttackEffectState FireAttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* FireEffectCollision_;
	GameEngineImage* Image_;
};
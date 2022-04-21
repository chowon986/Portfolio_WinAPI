#pragma once
#include <GameEngine/GameEngineActor.h>

enum class IceAttackEffectState
{
	IceAttackEffectRight,
	IceAttackEffectLeft,
	None,
};

class IceAttackEffect : public GameEngineActor
{
public:
	IceAttackEffect();
	~IceAttackEffect();

	IceAttackEffect(const IceAttackEffect& _Other) = delete;
	IceAttackEffect(IceAttackEffect&& _Other) noexcept = delete;
	IceAttackEffect& operator=(const IceAttackEffect& _Other) = delete;
	IceAttackEffect& operator=(IceAttackEffect&& _Other) noexcept = delete;

public:
	void SetState(IceAttackEffectState _IceAttackEffectState);
	IceAttackEffectState GetState();
private:
	void StateUpdate();
	void UpdateIceAttackEffectRight();
	void UpdateIceAttackEffectLeft();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	IceAttackEffectState IceAttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* IceEffectCollision_;
	GameEngineImage* Image_;
};
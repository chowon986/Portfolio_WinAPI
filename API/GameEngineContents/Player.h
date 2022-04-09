#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

enum class KirbyClass
{
	PIG,
	SPARK,
	SWORD,
	FIRE,
	ICE,
	ANIMAL,
	BEAM,
};


class GameEngineImage;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineLevel;
class Player : public CharacterBase
{
public:
	float4 PrevPos_;
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline void SetHPCount(int _HPCount) { HPCount_ = _HPCount; }
	inline int GetHPCount() { return HPCount_; }

protected:
	GameEngineCollision* KirbyCol_;

private:
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* AttackEffectRenderer_;
	GameEngineCollision* AttackEffectCol_;
	int HPCount_;

	float Gravity_;
	float AccGravity_;
	float JumpHeight_;
	float Time_;
	float Speed_;
	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;
	Player* Player_;
	KirbyClass KirbyClass_;
	CharacterState PrevState_;

	void SetPrevState(CharacterState _PrevState);
	CharacterState GetPrevState();

	void SetKirbyClass(KirbyClass _KirbyClass);
	KirbyClass GetKirbyClass();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void UpdateMove();
	void UpdateJump();
	void UpdateFly();
	void CorrectPos();

	void CheckCollision();

	void UpdateAnimation();

	virtual float GetSpeed() override;
	virtual bool CanWalk() override;
	virtual bool CanRun() override;
	virtual bool CanJump() override;
	
	bool CanFly();
	bool CanInhale();
	bool CanHover();
	bool CanEat();
	bool CanMoveUp();
	bool CanMoveDown();

	virtual void Walk() override;
	virtual void Run() override;
	/*virtual void Attack() override;
	virtual void Die() override;*/
	virtual void Jump() override;
	void MoveUp();
	void MoveDown();
	bool CheckMapCollision();
	void Hover();
	void Eat();
	void Fly();
	void Inhale();
	
};


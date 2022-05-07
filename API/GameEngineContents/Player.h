#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"
#include <string>


enum class KirbyClass
{
	DEFAULT,
	PIG,
	SPARK,
	SWORD,
	FIRE,
	ICE,
	ANIMAL,
};

enum class KirbyState
{
	IDLE,
	WALK, // possible : ATTACK, FLY, JUMP, EAT, ABANDON, SLIDE, TAKEDMG,  
	RUN,  // possible : ATTACK, FLY, JUMP, EAT, ABANDON, SLIDE, TKDMG,
	UP,	  // Animal 상태에서 땅 파고 올라가는 상태
	DOWN, // possible : SLIDE 
	SLIDE,  
	FLY, 
	FLYSTAY,
	FLYATTACK,
	FLYEND,
	EATSTART, // possible : ATTACK
	EAT,      // possible : ATTACK
	EATEND,   // possible : ATTACK
	ATTACK,	
	ATTACKSTAY,
	ABANDON,  
	TRANSFORM, 
	JUMPUP, // Possible : FLY
	JUMPING, // Possible : FLY
	JUMPDOWN, // Possible : FLY
	TAKEDAMAGE, // possible : ATTACK, FLY, JUMP, EAT, ABANDON, SLIDE,
	DIE,
	EATEN,
	OPENDOOR,
};

class GameEngineImage;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineLevel;
class BotUI;
class Monster;
class StarAttackEffect;
class AttackEffect;
enum class MonsterClass;
class IceAttackEffect;
class SparkAttackEffect;
class FireAttackEffect;
class SwordAttackEffect;
class DieEffect;
class RunEffect;
class GroundStarEffect;
class TransformEffect;
class AbandonEffect;
class Player : public CharacterBase
{
public:
	static int HP_COUNT;
	static int HP;
	static KirbyClass KIRBYCLASS;
	
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline void SetHPCount(int _HPCount) { HPCount_ = _HPCount; }
	inline int GetHPCount() { return HPCount_; }

	void SetKirbyClass(KirbyClass _KirbyClass);
	void SetState(KirbyState _PrevState);
	KirbyClass GetKirbyClass();
	KirbyState GetState() { return KirbyState_; }
	GameEngineRenderer* GetRenderer();
	void SetGravity(float _Gravity) { Gravity_ = _Gravity; }

private:
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* SparkRenderer_;
	GameEngineRenderer* PigRenderer_;
	GameEngineRenderer* SwimRenderer_;
	GameEngineRenderer* SwordRenderer_;
	GameEngineRenderer* FireRenderer_;
	GameEngineRenderer* IceRenderer_;
	GameEngineRenderer* AnimalRenderer_;

	GameEngineRenderer* AttackEffectRenderer_;

	GameEngineCollision* KirbyCol_;
	GameEngineCollision* KirbyEatCol_;
	GameEngineCollision* KirbySlideCol_;
	GameEngineCollision* AnimalCol_;
	GameEngineCollision* SwordCol_;

	GameEngineImage* Image_;
	GameEngineImage* SwordKirbyImage_;
	GameEngineImage* IceKirbyImage_;
	GameEngineImage* PigImage_;
	float4 StartPos_;
	float4 MapStartPos_;

	AbandonEffect* AbandonEffect_;
	StarAttackEffect* StarAttackEffect_;
	AttackEffect* AttackEffect_;
	IceAttackEffect* IceAttackEffect_;
	SparkAttackEffect* SparkAttackEffect_;
	FireAttackEffect* FireAttackEffect_;
	SwordAttackEffect* SwordAttackEffect_;
	TransformEffect* TransformEffect_;
	DieEffect* DieEffect_;
	RunEffect* RunEffect_;
	GroundStarEffect* GroundStarEffect_;

	Monster* Monster_;
	MonsterClass MonClass_;


	int HPCount_;
	float Gravity_;
	float JumpHeight_;
	float Time_;
	float AttTime_;
	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;
	KirbyClass KirbyClass_;
	KirbyState KirbyState_;
	std::string Dir_;
	bool IsGround_;

	void ClassUpdate();

	virtual void Start() override;
	virtual void DelayUpdate() override;
	virtual void Render() override;

	void CorrectPos();

	void CheckCollision();
	void StateUpdate();
	bool CheckMapCollision();

	void UpdateIdle();
	void UpdateWalk();
	void UpdateRun();
	void UpdateFly();
	void UpdateFlyStay();
	void UpdateFlyAttack();
	void UpdateFlyEnd();
	void UpdateAttack();
	void UpdateAttackStay();
	void UpdateDie();
	void UpdateUp();
	void UpdateDown();
	void UpdateHover();
	void UpdateInhale();
	void UpdateEatStart();
	void UpdateEat();
	void UpdateEatEnd();
	void UpdateJumpUp();
	void UpdateJumping();
	void UpdateJumpDown();
	void UpdateSlide();
	void UpdateTransform();
	void UpdateTransformEnd();
	void UpdateTakeDamage();
	void UpdateAbandon();
	void UpdateEaten();
	void UpdateOpenDoor();

	//void UpdateEffect();
public:
	void SetDieEffect(DieEffect* _DieEffect)
	{
		DieEffect_ = _DieEffect;
	}

	void SetMapStartPos(float4 _MapStartPos)
	{ 
		MapStartPos_ = _MapStartPos;
	}

	void SetAbandonEffect(AbandonEffect* _AbandonEffect)
	{
		AbandonEffect_ = _AbandonEffect;
	}

	void SetStarAttackEffect(StarAttackEffect* _StarAttackEffect)
	{
		StarAttackEffect_ = _StarAttackEffect;
	}

	void SetAttackEffect(AttackEffect* _AttackEffect)
	{
		AttackEffect_ = _AttackEffect;
	}

	void SetIceAttackEffect(IceAttackEffect* _IceAttackEffect)
	{
		IceAttackEffect_ = _IceAttackEffect;
	}	
	
	void SetSparkAttackEffect(SparkAttackEffect* _SparkAttackEffect)
	{
		SparkAttackEffect_ = _SparkAttackEffect;
	}

	void SetSwordAttackEffect(SwordAttackEffect* _SwordAttackEffect)
	{
		SwordAttackEffect_ = _SwordAttackEffect;
	}

	void SetFireAttackEffect(FireAttackEffect* _FireAttackEffect)
	{
		FireAttackEffect_ = _FireAttackEffect;
	}

	void SetTransformEffect(TransformEffect* _TransformEffect)
	{
		TransformEffect_ = _TransformEffect;
	}

	void SetRunEffect(RunEffect* _RunEffect)
	{
		RunEffect_ = _RunEffect;
	}

	void SetGroundStarEffect(GroundStarEffect* _GroundStarEffect)
	{
		GroundStarEffect_ = _GroundStarEffect;
	}

	void SetHP(int _HP) override;
};

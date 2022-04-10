#pragma once
#include <GameEngine/GameEngineActor.h>


class CharacterBase : public GameEngineActor
{
private:
	int HP_;
	float Speed_;
	float JumpMaxHeight_;
	float JumpHeight_;
	float4 JumpDirection_;

protected:
	CharacterBase();
	virtual ~CharacterBase();

	CharacterBase(const CharacterBase& _Other) = delete;
	CharacterBase(CharacterBase&& _Other) noexcept = delete;
	CharacterBase& operator=(const CharacterBase& _Other) = delete;
	CharacterBase& operator=(CharacterBase&& _Other) noexcept = delete;

protected:

public:
	virtual void SetHP(int _HP) { HP_ = _HP; }
	void SetJumpHeight(float _JumpHeight) { JumpHeight_ = _JumpHeight; }
	void SetSpeed(float _Speed) { Speed_ = _Speed; }
	void SetJumpDirection(float4 _JumpDirection)
	{
		// if (_JumpDirection == float4::UP || _JumpDirection == float4::DOWN)
		{
			JumpDirection_ = _JumpDirection;
		}
	}

	int GetHP() { return HP_; }
	virtual float GetSpeed() { return Speed_; }
	float GetJumpHeight() { return JumpHeight_; }
	float GetJumpMaxHeight() { return JumpMaxHeight_; }
	float4 GetJumpDirection() { return JumpDirection_; }

	virtual bool CanRun() { return false; }
	virtual bool CanWalk() { return false; }
	virtual bool CanJump() { return false; }

	virtual void Walk() {}
	virtual void Run() {}
	/*virtual void Attack();
	virtual void Die();*/
	virtual void Jump() {}

};

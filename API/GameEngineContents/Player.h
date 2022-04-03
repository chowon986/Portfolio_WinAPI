#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

class GameEngineImage;
class GameEngineRenderer;
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	float Gravity_;
	float AccGravity_;
	float4 PrevPos_;

	void Start() override;
	void Render() override;
	void Update() override;

	virtual float GetSpeed() override;

	virtual bool CanWalk() override;
	virtual bool CanRun() override;
	virtual bool CanJump() override;
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
};


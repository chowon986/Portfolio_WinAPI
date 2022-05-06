#pragma once
#include "Obstruction.h"

class Ground : public GameEngineActor
{
public:
	Ground();
	~Ground();

	Ground(const Ground& _Other) = delete;
	Ground(Ground&& _Other) noexcept = delete;
	Ground& operator=(const Ground& _Other) = delete;
	Ground& operator=(Ground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	GameEngineCollision* Collision_;
	GameEngineCollision* MoveCollision_;
	GameEngineRenderer* Renderer_;

public:
	GameEngineRenderer* GetRenderer() { return Renderer_; }
};

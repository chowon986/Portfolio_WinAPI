#pragma once
#include "Obstruction.h"

class Ground : public Obstruction
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
	void ColUpdate() override;

private:

public:
	GameEngineRenderer* GetRenderer() { return Renderer_; }
};

#pragma once
#include "Obstruction.h"

class BigBox : public Obstruction
{
public:
	BigBox();
	~BigBox();

	BigBox(const BigBox& _Other) = delete;
	BigBox(BigBox&& _Other) noexcept = delete;
	BigBox& operator=(const BigBox& _Other) = delete;
	BigBox& operator=(BigBox&& _Other) noexcept = delete;

protected:
	void Start();
	void DelayUpdate();

private:
};

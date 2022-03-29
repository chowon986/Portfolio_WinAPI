#pragma once
#include "Monster.h"

class BigWaddledi : public Monster
{
public:
	BigWaddledi();
	~BigWaddledi();

	BigWaddledi(const BigWaddledi& _Other) = delete;
	BigWaddledi(BigWaddledi&& _Other) noexcept = delete;
	BigWaddledi& operator=(const BigWaddledi& _Other) = delete;
	BigWaddledi& operator=(BigWaddledi&& _Other) noexcept = delete;

public:
	void Start();
protected:

private:

};
#pragma once
#include "Monster.h"

class HPUp : public Monster
{
public:
	HPUp();
	~HPUp();

	HPUp(const HPUp& _Other) = delete;
	HPUp(HPUp&& _Other) noexcept = delete;
	HPUp& operator=(const HPUp& _Other) = delete;
	HPUp& operator=(HPUp&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};
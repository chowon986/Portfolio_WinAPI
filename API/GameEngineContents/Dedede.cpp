#include "Dedede.h"

Dedede::Dedede()
	: Monster()
{
	SetMonsterClass(MonsterClass::BOSS);
}

Dedede::~Dedede()
{
}

void Dedede::Start()
{
}

void Dedede::Render()
{
}

void Dedede::Update()
{
}

bool Dedede::CheckMapCollision()
{
	if(GetLevel()->GetColMapImage())
	return false;
}

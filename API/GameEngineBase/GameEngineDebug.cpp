#include "GameEngineDebug.h"



GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug()
{
}

void GameEngineDebug::LeakCheckOn() // ¸¯ Ã¼Å©
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

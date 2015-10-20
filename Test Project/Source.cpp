#include "LoopHandle.h"

int wmain()
{
	LoopHandle::Init();
	LoopHandle::Handle();
	LoopHandle::Quit();

	return 0;
}
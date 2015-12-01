#ifndef _GAMETIME_H_
#define _GAMETIME_H_

#include <time.h>

namespace Time
{
	extern float fDeltaTime;

	int Init(const float ac_fScaleFactor = 1);

	void Update();

	void SetScaleFactor(const float ac_fScaleFactor);

	void Quit();
}

#endif // _GAMETIME_H_
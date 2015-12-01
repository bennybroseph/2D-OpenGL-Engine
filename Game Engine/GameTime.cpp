#include "GameTime.h"

const unsigned int ONE_SECOND = 1000;

namespace Time
{
	int iCurrentTime, iPreviousTime;
	float fDeltaTime;

	float fScaleFactor;

	int Init(const float ac_fScaleFactor)
	{
		iCurrentTime = clock();
		iPreviousTime = iCurrentTime;

		fDeltaTime = NULL;

		fScaleFactor = ac_fScaleFactor;

		return 0;
	}

	void Update()
	{
		iPreviousTime = iCurrentTime;
		iCurrentTime = clock();

		fDeltaTime = (iCurrentTime - iPreviousTime) / (ONE_SECOND * fScaleFactor);
	}

	void SetScaleFactor(const float ac_fScaleFactor)
	{
		fScaleFactor = ac_fScaleFactor;
	}

	void Quit()
	{

	}
}
#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_

#include <time.h>

class GameTimer
{
private:
	int m_iCurrentTime, m_iPrevTime;


public:
	void Update();



	GameTimer();
	~GameTimer();
};

#endif // _GAMETIMER_H_
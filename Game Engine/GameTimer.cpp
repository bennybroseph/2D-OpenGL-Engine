#include "GameTimer.h"



void GameTimer::Update()
{

}

GameTimer::GameTimer()
{
	m_iCurrentTime = clock();
	m_iPrevTime = m_iCurrentTime;
}


GameTimer::~GameTimer()
{

}

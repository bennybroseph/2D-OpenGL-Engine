////////////////////////////////////////////////////////////
// File: Loop.cpp
// Author: Ben Odom
// Date Created: 10/01/2015
////////////////////////////////////////////////////////////

#include "Loop.h"

namespace LoopHandle
{
	Loop::Loop()
	{
		m_bRunning = true;
	}

	Loop::~Loop()
	{
	}

	void Loop::Run()
	{
		while (m_bRunning)
		{
			while (SDL_PollEvent(&m_sdlEvent))
			{
				//Calls the redefined event function for the class
				OnEvent(m_sdlEvent);
			}
			Update();

			LateUpdate();

			Graphics::Draw();
			Draw();
			Graphics::Flip();
		}
	}

	//Empty because it is virtual only
	void Loop::Update()
	{

	}
	//Empty because it is virtual only
	void Loop::LateUpdate()
	{

	}
	//Empty because it is virtual only
	void Loop::Draw()
	{

	}
}

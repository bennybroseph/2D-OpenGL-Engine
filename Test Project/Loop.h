////////////////////////////////////////////////////////////
// File: Loop.h
// Author: Ben Odom
// Date Created: 10/01/2015
// Brief: This file contains the template for all other 
//		  loops in the project
////////////////////////////////////////////////////////////

#ifndef LOOP_H_INCLUDED
#define LOOP_H_INCLUDED

#include "Graphics.h"
#include "EventHandler.h"

namespace LoopHandle
{
	class Loop : public EH
	{
	public:
		///////Constructor - Destructor//////
		Loop();

		// Must be virtual if other functions are virtual
		virtual ~Loop();

		// Contains a simple loop that runs the virtual event
		// Reason this is cool is because as each child of Loop redefines the event functions,
		// it will call the redefined ones, so every child can use the same loop
		void Run();

		// Redefined for each child
		virtual void Update();
		// Redefined for each child
		virtual void LateUpdate();

	protected:
		//////Member Variables//////
		// Keeps the loop running
		bool m_bRunning;

		// Stores events that happen during the loop
		SDL_Event m_sdlEvent;
	};
}

#endif // LOOP_H_INCLUDED

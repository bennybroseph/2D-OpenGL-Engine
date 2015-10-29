////////////////////////////////////////////////////////////
// File: LoopHandle.h
// Author: Ben Odom
// Date Created: 10/01/2015
// Brief: Meant to contain all "while(running)" loops
//		  To use, create a member function called something 
//		  appropriate, and copy the shell loop into the 
//		  function. Meant to work by calling functions of 
//		  all other namespaces. You should create a member 
//		  function for each loop you would run
//		  Ex: Loop for menu, then loop for single-player, 
//		  loop for options, etc.
////////////////////////////////////////////////////////////

#ifndef LOOPS_H_INCLUDED
#define LOOPS_H_INCLUDED

#include "GameLoop.h"

#include <Graphics.h>

#include <windows.h>

namespace LoopHandle
{
    //Inits all other namespaces of the engine
    void Init();

    //The main handle loop
	void Handle();

    //Calls the Quit() functions of all other namespaces and frees memory before program exit
    void Quit();
}

#endif // LOOPS_H_INCLUDED

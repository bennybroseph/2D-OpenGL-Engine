//////////////////////////////////////////////////////////////
// File: EventHandler.h
// Author: Ben Odom
// Brief: You're not meant to create an object of this class
//		  This class is created to simply be inherited by 
//        'Loop'. By making all virtual, each object of 
//        'Loops' (or its children) can redefine what 
//        happens on that event
//////////////////////////////////////////////////////////////

#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include <stdio.h>
#include <SDL.h>

class EventHandler
{
protected:
	//////Constructor - Destructor//////

	EventHandler();
	//This should be virtual if any member function is virtual
	virtual ~EventHandler();

	//////Functions//////

	//Takes in the event, and then calls the appropriate function
	virtual void OnEvent(const SDL_Event& ac_sdlEvent);

	//Deals with window focus (alt-tab)
	virtual void OnInputFocus();
	virtual void OnInputBlur();

	//Takes in sym (The enum naming the key) the mod (if any, like shift), and unicode (in case of typing)
	virtual void OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);
	virtual void OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);

	//Deals with window focus (clicking in and out)
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();

	//Passes mouse_x mouse_y x_velocity y_velocity  buttonL,  buttonR,      buttonM (scroll wheel)
	virtual void OnMouseMove(const Sint32 ac_iMouseX, const Sint32 ac_iMouseY, const Sint32 ac_iVelX, const Sint32 ac_VelY, const bool ac_bLeft, const bool ac_bRight, const bool ac_bMiddle);

	//Passes which way the mouse wheel is spun
	virtual void OnMouseWheel(const Sint32 ac_iVelX, const Sint32 ac_iVelY);

	//If mouse buttons down/up
	virtual void OnLButtonDown(const Sint32 ac_MouseX, const Sint32 ac_MouseY);
	virtual void OnLButtonUp(const Sint32 ac_MouseX, const Sint32 ac_MouseY);
	virtual void OnRButtonDown(const Sint32 ac_MouseX, const Sint32 ac_MouseY);
	virtual void OnRButtonUp(const Sint32 ac_MouseX, const Sint32 ac_MouseY);
	virtual void OnMButtonDown(const Sint32 ac_MouseX, const Sint32 ac_MouseY);
	virtual void OnMButtonUp(const Sint32 ac_MouseX, const Sint32 ac_MouseY);

	//Checks for joystick events, but there's an SDL_Joystick object which is much better
	virtual void OnJoyAxis(const Uint8 ac_uiWhich, const Uint8 ac_uiAxis, const Sint16 ac_uiValue);
	virtual void OnJoyButtonDown(const Uint8 ac_uiWhich, const Uint8 ac_uiButton);
	virtual void OnJoyButtonUp(const Uint8 ac_uiWhich, const Uint8 ac_uiButton);
	virtual void OnJoyHat(const Uint8 ac_uiWhich, const Uint8 ac_uiHat, const Uint8 ac_uiValue);
	virtual void OnJoyBall(const Uint8 ac_uiWhich, const Uint8 ac_uiBall, const Sint16 ac_uiRelX, const Sint16 ac_uiRelY);

	//Minimize and maximize of window
	virtual void OnMinimize();
	virtual void OnRestore();

	//When the window gets resized, returns the new W and H
	virtual void OnResize(const Sint32 ac_iWidth, const Sint32 ac_iHeight);

	//Most likely when the window is restored from being minimized?
	virtual void OnExpose();

	//Can be different for each class that defines it
	virtual void OnExit();

	//No clue
	virtual void OnUser(const Uint32 ac_uiType, const Sint32 ac_iCode, const void* ac_pData1, const void* ac_pData2);
};

//Renames EventHandler as EH
//With this, instead of doing EventHandler* handle = new EventHandler,
//You can do EH* handle = new EH
typedef EventHandler EH;

#endif // _EVENTHANDLER_H_

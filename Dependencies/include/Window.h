#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "System.h"

#include <vector>
#include <SDL.h>

#include <glfw3.h>

namespace Graphics
{
	class Window
	{
	private:
		SDL_Window* m_sdlWindow;

		const std::vector<SDL_DisplayMode>& m_sdlDisplayMode;

		System::Size2D<unsigned int> m_uiDimensions;
		System::Size2D<unsigned int> m_uiNonFullscreen;
		System::Size2D<unsigned int> m_uiResolution;

		System::Size2D<unsigned int>  m_uiViewport;
		System::Point2D<unsigned int> m_uiViewOffset;

		std::string m_sTitle;

		bool m_bIsFullscreen;

		unsigned int m_uiMonitorIndex;

	public:
		void Resize(const System::Size2D<unsigned int> &ac_uiNewDimensions, const unsigned int ac_uiMonitorIndex);
		void Rename(const char *ac_szNewTitle);

		void ToggleFullscreen();

		const System::Size2D<unsigned int>& GetDimensions();
		const System::Size2D<unsigned int>& GetNonFullscreen();

		SDL_Window* GetWindow();
		const SDL_GLContext& GetContext();
		const System::Size2D<unsigned int>& GetResolution();

		const bool GetIsFullscreen();

		void Flip();

		// This is the only usable constructor
		Window(
			const System::Size2D<unsigned int>& ac_iResolution,		// The window's internal resolution
			const bool							ac_bFullscreen,		// Whether or not the window should be full screen on creation
			const System::Size2D<unsigned int>& ac_iDimensions,		// The window's width and height
			const char*							ac_szTitle,			// The window's title
			const unsigned int					ac_uiMonitorIndex,	// Which monitor the window should be created on
			const std::vector<SDL_DisplayMode>&	ac_sdlDisplayMode); // A reference to all the current displays dimensions and specifications
																	// The default constructor does not exist on purpose
		Window() = delete; // Make sure the default constructor cannot be called
		~Window();
	};
	extern std::vector<SDL_DisplayMode> sdlDisplayMode;
	extern SDL_GLContext glContext;

	extern std::vector<Window*>	voWindows; // The vector that holds each 'Window' object

	/* - Creates a 'new Window' and pushes it into the 'voWindows' vector
	Parameters:
	- The window's internal resolution
	- Whether or not the window should be full screen on creation
	- The window's width and height
	- The window's title -- Default = "New Window"
	- Which monitor the window should be created on -- Default = 0
	*/
	void NewWindow(
		const System::Size2D<unsigned int>& ac_iResolution,				// The window's internal resolution
		const bool						    ac_bFullscreen,				// Whether or not the window should be full screen on creation
		const System::Size2D<unsigned int>& ac_iDimensions,				// The window's width and height
		const char*							ac_szTitle = "New Window",	// The window's title
		const unsigned int					ac_uiMonitorIndex = 0);		// Which monitor the window should be created on
}

#endif // _WINDOW_H_
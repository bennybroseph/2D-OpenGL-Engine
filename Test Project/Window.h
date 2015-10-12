#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "System.h"

#include <vector>
#include <SDL.h>
#include <glut.h>

namespace Graphics
{
	class Window
	{
	private:
		SDL_Window* m_sdlWindow;
		SDL_GLContext m_glContext;

		const std::vector<SDL_DisplayMode>& m_sdlDisplayMode;

		System::Size2D<unsigned int> m_uiDimensions;
		System::Size2D<unsigned int> m_uiResolution;

		System::Size2D<unsigned int>  m_uiViewport;
		System::Point2D<unsigned int> m_uiViewOffset;

		std::string m_sTitle;

		bool m_bIsFullscreen;

		unsigned int m_uiMonitorIndex;

	public:
		void SetResolution(const System::Size2D<unsigned int> &ac_uiNewResolution);

		void Resize(const System::Size2D<unsigned int> &ac_uiNewDimensions, const unsigned int ac_uiMonitorIndex);
		void Rename(const char *ac_szNewTitle);

		void ToggleFullscreen();

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
}

#endif // _WINDOW_H_
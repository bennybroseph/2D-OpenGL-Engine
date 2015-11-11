////////////////////////////////////////////////////////////
// File: Window.cpp
// Author: Ben Odom
// Date Created: 10/01/2015
////////////////////////////////////////////////////////////

#include "Window.h"


namespace Graphics
{
	void NewWindow(
		const System::Size2D<unsigned int>& ac_uiResolution,
		const bool							ac_bFullscreen,
		const System::Size2D<unsigned int>& ac_uiSize,
		const char*							ac_szTitle,
		const unsigned int					ac_uiMonitorIndex)
	{
		voWindows.push_back(new Window(
			ac_uiResolution,
			ac_bFullscreen,
			ac_uiSize,
			ac_szTitle,
			ac_uiMonitorIndex,
			sdlDisplayMode));

		if (glContext == nullptr)
		{
			glContext = SDL_GL_CreateContext(voWindows[0]->GetWindow());

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			SDL_GL_SetSwapInterval(-1);

			glViewport(0, 0, ac_uiSize.W, ac_uiSize.H);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glOrtho(-1.0f, ac_uiResolution.W, ac_uiResolution.H, 0.0f, 0.0f, 1.0f);
		}
	}
}

namespace Graphics
{
	void Window::Resize(const System::Size2D<unsigned int>& ac_uiNewDimensions, const unsigned int ac_uiNewMonitorIndex)
	{
		m_uiMonitorIndex = ac_uiNewMonitorIndex;

		m_uiSize.W = (m_bIsFullscreen) ? m_sdlDisplayMode[m_uiMonitorIndex].w : ac_uiNewDimensions.W;
		m_uiSize.H = (m_bIsFullscreen) ? m_sdlDisplayMode[m_uiMonitorIndex].h : ac_uiNewDimensions.H;

		m_uiWindowedSize = ac_uiNewDimensions;

		if (m_bIsFullscreen)
			SDL_SetWindowFullscreen(m_sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP*m_bIsFullscreen);
		else
		{
			SDL_SetWindowFullscreen(m_sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP*m_bIsFullscreen);
			SDL_SetWindowSize(m_sdlWindow, m_uiWindowedSize.W, m_uiWindowedSize.H);
			SDL_SetWindowPosition(m_sdlWindow, SDL_WINDOWPOS_CENTERED_DISPLAY(m_uiMonitorIndex), SDL_WINDOWPOS_CENTERED_DISPLAY(m_uiMonitorIndex));
		}
	}
	void Window::Rename(const char* ac_szNewTitle)
	{
		m_sTitle = ac_szNewTitle;
		SDL_SetWindowTitle(m_sdlWindow, m_sTitle.c_str());
	}

	void Window::ToggleFullscreen()
	{
		m_bIsFullscreen = !m_bIsFullscreen;
		Resize(m_uiWindowedSize, m_uiMonitorIndex);
	}

	const System::Size2D<unsigned int>& Window::GetDimensions()
	{
		return m_uiSize;
	}
	const System::Size2D<unsigned int>& Window::GetNonFullscreen()
	{
		return m_uiWindowedSize;
	}

	SDL_Window* Window::GetWindow()
	{
		return m_sdlWindow;
	}
	const System::Size2D<unsigned int>& Window::GetResolution()
	{
		return m_uiResolution;
	}

	const bool Window::GetIsFullscreen()
	{
		return m_bIsFullscreen;
	}

	void Window::Flip()
	{
		SDL_GL_SwapWindow(m_sdlWindow);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	Window::Window(
		const System::Size2D<unsigned int>& ac_uiResolution,
		const bool							ac_bFullscreen,
		const System::Size2D<unsigned int>& ac_uiSize,
		const char*							ac_szTitle,
		const unsigned int					ac_uiMonitorIndex,
		const std::vector<SDL_DisplayMode>&	ac_sdlDisplayMode) : m_sdlDisplayMode(ac_sdlDisplayMode)
	{
		m_uiMonitorIndex = ac_uiMonitorIndex;

		m_uiSize.W = (ac_bFullscreen) ? m_sdlDisplayMode[m_uiMonitorIndex].w : ac_uiSize.W;
		m_uiSize.H = (ac_bFullscreen) ? m_sdlDisplayMode[m_uiMonitorIndex].h : ac_uiSize.H;

		m_uiWindowedSize = ac_uiSize;

		m_uiResolution = ac_uiResolution;

		m_sTitle = ac_szTitle;

		m_bIsFullscreen = ac_bFullscreen;

		m_sdlWindow = SDL_CreateWindow(
			m_sTitle.c_str(),
			SDL_WINDOWPOS_CENTERED_DISPLAY(m_uiMonitorIndex),
			SDL_WINDOWPOS_CENTERED_DISPLAY(m_uiMonitorIndex),
			m_uiWindowedSize.W,
			m_uiWindowedSize.H,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP*m_bIsFullscreen | SDL_WINDOW_OPENGL);

		if (m_sdlWindow == nullptr)
			printf("SDL_Error: %s\n", SDL_GetError());
	}
	Window::~Window()
	{

	}
}
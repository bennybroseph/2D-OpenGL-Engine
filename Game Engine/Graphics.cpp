#include "Graphics.h"


namespace Graphics
{
	std::vector<SDL_DisplayMode> sdlDisplayMode;
	SDL_GLContext glContext;
	unsigned int uiNumDisplays;

	std::vector<Window*>		voWindows;
	std::vector<CameraUnion*>	voCameras;

	std::vector<SurfaceUnion*> vglSurfaces;

	bool Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		if ((uiNumDisplays = SDL_GetNumVideoDisplays()) < 1)
		{
			SDL_Log("SDL_GetNumVideoDisplays returned: %i", uiNumDisplays);
			return 1;
		}

		for (unsigned int i = 0; i < uiNumDisplays; ++i)
		{
			SDL_DisplayMode sdlTemp;
			if (SDL_GetDisplayMode(i, i, &sdlTemp) != 0)
				printf("SDL_GetDisplayMode failed: %s", SDL_GetError());
			else
				sdlDisplayMode.push_back(sdlTemp);
		}

		glContext = nullptr;

		return 0;
	}

	void Resize(
		const System::Size2D<unsigned int>& ac_uiNewDimensions,
		const unsigned int					ac_uiNewMonitorIndex,
		const unsigned int					ac_uiIndex)
	{
		for (unsigned int i = 0; i < voCameras.size(); ++i)
		{
			switch (voCameras[i]->Tag)
			{
			case CameraUnion::INT: ResizeCameras(*voCameras[i]->iCamera, ac_uiNewDimensions, ac_uiIndex); break;
			case CameraUnion::FLOAT: ResizeCameras(*voCameras[i]->fCamera, ac_uiNewDimensions, ac_uiIndex); break;
			}
		}
		voWindows[ac_uiIndex]->Resize(ac_uiNewDimensions, ac_uiNewMonitorIndex);
	}
	void ToggleFullscreen(const unsigned int ac_uiIndex)
	{
		System::Size2D<unsigned int> NewDimensions;
		NewDimensions.W = (!voWindows[ac_uiIndex]->GetIsFullscreen()) ? (unsigned int)sdlDisplayMode[ac_uiIndex].w : voWindows[ac_uiIndex]->GetNonFullscreen().W;
		NewDimensions.H = (!voWindows[ac_uiIndex]->GetIsFullscreen()) ? (unsigned int)sdlDisplayMode[ac_uiIndex].h : voWindows[ac_uiIndex]->GetNonFullscreen().H;

		for (unsigned int i = 0; i < voCameras.size(); ++i)
		{
			switch (voCameras[i]->Tag)
			{
			case CameraUnion::INT: ResizeCameras(*voCameras[i]->iCamera, NewDimensions, ac_uiIndex); break;
			case CameraUnion::FLOAT: ResizeCameras(*voCameras[i]->fCamera, NewDimensions, ac_uiIndex); break;
			}
		}

		voWindows[ac_uiIndex]->ToggleFullscreen();
	}

	void Draw()
	{
		for (unsigned int i = 0; i < voCameras.size(); ++i)
		{
			switch (voCameras[i]->Tag)
			{
			case CameraUnion::INT:	 UpdateCameras(*voCameras[i]->iCamera); break;
			case CameraUnion::FLOAT: UpdateCameras(*voCameras[i]->fCamera); break;
			}
		}
	}

	template <typename T>
	void UpdateCameras(Camera<T>& a_Camera)
	{
		a_Camera.Update();

		SDL_GL_MakeCurrent(voWindows[a_Camera.GetWindowIndex()]->GetWindow(), glContext);

		glViewport(
			(GLsizei)a_Camera.GetScreenPos().X,
			(GLsizei)a_Camera.GetScreenPos().Y,
			(GLsizei)a_Camera.GetDimensions().W,
			(GLsizei)a_Camera.GetDimensions().H);
		glMatrixMode(GL_MODELVIEW);

		glOrtho(
			0.0f,
			a_Camera.GetResolution().W,
			a_Camera.GetResolution().H,
			0.0f, -1.0f, 1.0f);
		glLoadIdentity();

		glPushMatrix(); // Save the current matrix.

		glTranslatef((GLfloat)(a_Camera.GetResolution().W / 2), (GLfloat)(a_Camera.GetResolution().H / 2), 0.0f);	// Move the world space based on the camera's position and center it
		glScalef((GLfloat)a_Camera.GetZoom().W, (GLfloat)a_Camera.GetZoom().H, 0.0f);								// Scale the world space based on the camera's scale
		glRotatef((GLfloat)a_Camera.GetRotation(), 0.0f, 0.0f, 1.0f);												// Rotate the world space based on the camera's rotation
		glTranslatef(																								// Move the world space based on the camera's position
			(GLfloat)(-a_Camera.GetWorldPos().X),
			(GLfloat)(-a_Camera.GetWorldPos().Y), 0.0f);


		for (unsigned int i = 0; i < vglSurfaces.size(); ++i)
		{
			switch (vglSurfaces[i]->Tag)
			{
			case SurfaceUnion::INT:
			{
				if (vglSurfaces[i]->iGLSurface->bIsActive && a_Camera.GetWorldSpace() == vglSurfaces[i]->iGLSurface->uiWorldSpace)
				{
					ManipulateSurface(*vglSurfaces[i]->iGLSurface);
				}
				break;
			}
			case SurfaceUnion::FLOAT:
			{
				if (vglSurfaces[i]->fGLSurface->bIsActive && a_Camera.GetWorldSpace() == vglSurfaces[i]->fGLSurface->uiWorldSpace)
				{
					ManipulateSurface(*vglSurfaces[i]->fGLSurface);
				}
				break;
			}
			}
		}

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}

	void Sort()
	{
		std::sort(vglSurfaces.begin(), vglSurfaces.end(), SortCamera);
		std::sort(vglSurfaces.begin(), vglSurfaces.end(), SortLayer);
	}

	bool SortLayer(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight)
	{
		switch (ac_pglLeft->Tag)
		{
		case SurfaceUnion::INT:
		{
			switch (ac_pglRight->Tag)
			{
			case SurfaceUnion::INT:
			{
				if (ac_pglLeft->iGLSurface->uiWorldSpace == ac_pglRight->iGLSurface->uiWorldSpace)
					return ac_pglLeft->iGLSurface->Layer < ac_pglRight->iGLSurface->Layer;
				break;
			}
			case SurfaceUnion::FLOAT:
			{
				if (ac_pglLeft->iGLSurface->uiWorldSpace == ac_pglRight->fGLSurface->uiWorldSpace)
					return ac_pglLeft->iGLSurface->Layer < ac_pglRight->fGLSurface->Layer;
				break;
			}
			}
			break;
		}
		case SurfaceUnion::FLOAT:
		{
			switch (ac_pglRight->Tag)
			{
			case SurfaceUnion::INT:
			{
				if (ac_pglLeft->fGLSurface->uiWorldSpace == ac_pglRight->iGLSurface->uiWorldSpace)
					return ac_pglLeft->fGLSurface->Layer < ac_pglRight->iGLSurface->Layer;
				break;
			}
			case SurfaceUnion::FLOAT:
			{
				if (ac_pglLeft->fGLSurface->uiWorldSpace == ac_pglRight->fGLSurface->uiWorldSpace)
					return ac_pglLeft->fGLSurface->Layer < ac_pglRight->fGLSurface->Layer;
				break;
			}
			}
			break;
		}
		}

		return false;
	}
	bool SortCamera(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight)
	{
		switch (ac_pglLeft->Tag)
		{
		case SurfaceUnion::INT:
		{
			switch (ac_pglRight->Tag)
			{
			case SurfaceUnion::INT:	  return ac_pglLeft->iGLSurface->uiWorldSpace < ac_pglRight->iGLSurface->uiWorldSpace; break;
			case SurfaceUnion::FLOAT: return ac_pglLeft->iGLSurface->uiWorldSpace < ac_pglRight->fGLSurface->uiWorldSpace; break;
			}
			break;
		}
		case SurfaceUnion::FLOAT:
		{
			switch (ac_pglRight->Tag)
			{
			case SurfaceUnion::INT:	  return ac_pglLeft->fGLSurface->uiWorldSpace < ac_pglRight->iGLSurface->uiWorldSpace; break;
			case SurfaceUnion::FLOAT: return ac_pglLeft->fGLSurface->uiWorldSpace < ac_pglRight->fGLSurface->uiWorldSpace; break;
			}
			break;
		}
		default: return false;
		}
		return false;
	}

	void Flip()
	{
		for (unsigned int i = 0; i < voWindows.size(); ++i)
		{
			SDL_GL_MakeCurrent(voWindows[i]->GetWindow(), glContext);
			voWindows[i]->Flip();
		}
	}

	void Quit()
	{
		voWindows.clear();
		voCameras.clear();
		vglSurfaces.clear();
	}
}
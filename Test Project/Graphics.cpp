#include "Graphics.h"



namespace Graphics
{
	std::vector<SDL_DisplayMode> sdlDisplayMode;
	unsigned int uiNumDisplays;

	std::vector<Window*>		voWindows;
	std::vector<CameraUnion*>	voCameras;

	std::vector<SurfaceUnion*> vglSurfaces;

	bool Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		if (uiNumDisplays = SDL_GetNumVideoDisplays() < 1)
		{
			SDL_Log("SDL_GetNumVideoDisplays returned: %i", uiNumDisplays);
			return 1;
		}

		for (int i = 0; i < uiNumDisplays; ++i)
		{
			if (SDL_GetDisplayMode(i, i, &sdlDisplayMode[i]) != 0)
			{
				printf("SDL_GetDisplayMode failed: %s", SDL_GetError());
			}
		}

		return 0;
	}

	void NewWindow(
		const System::Dimensions<unsigned int>& ac_iResolution,
		const bool								ac_bFullscreen,
		const System::Dimensions<unsigned int>& ac_iDimensions,
		const char*								ac_szTitle,
		const unsigned int						ac_uiMonitorIndex)
	{
		voWindows.push_back(new Window(
			ac_iResolution,
			ac_bFullscreen,
			ac_iDimensions,
			ac_szTitle,
			ac_uiMonitorIndex,
			sdlDisplayMode));
	}

	void NewCamera(
		const System::Point2D<int>&	   ac_iScreenPos,
		const System::Point2D<int>&	   ac_iWorldPos,
		const System::Point2D<int>&	   ac_iRelativePos,
		const System::Dimensions<int>& ac_iDimensions,
		const bool					   ac_bIsScrolling,
		const System::Velocity<int>&   ac_iVelocity,
		const unsigned int			   ac_uiWindowIndex)
	{
		CameraUnion* newCamera = new CameraUnion;

		newCamera->Tag = CameraUnion::INT;
		newCamera->iCamera = new Camera<int>(ac_iScreenPos, ac_iWorldPos, ac_iRelativePos, ac_iDimensions, ac_bIsScrolling, ac_iVelocity, ac_uiWindowIndex);
		voCameras.push_back(newCamera);
	}
	void NewCamera(
		const System::Point2D<float>&	 ac_fScreenPos,
		const System::Point2D<float>&	 ac_fWorldPos,
		const System::Point2D<float>&	 ac_fRelativePos,
		const System::Dimensions<float>& ac_fDimensions,
		const bool						 ac_bIsScrolling,
		const System::Velocity<float>&	 ac_fVelocity,
		const unsigned int				 ac_uiWindowIndex)
	{
		CameraUnion* newCamera = new CameraUnion;

		newCamera->Tag = CameraUnion::FLOAT;
		newCamera->fCamera = new Camera<float>(ac_fScreenPos, ac_fWorldPos, ac_fRelativePos, ac_fDimensions, ac_bIsScrolling, ac_fVelocity, ac_uiWindowIndex);
		voCameras.push_back(newCamera);
	}

	void Draw()
	{
		ReOrder();

		for (int i = 0; i < vglSurfaces.size(); ++i)
		{
			switch (vglSurfaces[i]->Tag)
			{
			case SurfaceUnion::INT:
			{
				switch (voCameras[vglSurfaces[i]->iGLSurface->uiCameraIndex]->Tag)
				{
				case CameraUnion::INT:
				{
					if (vglSurfaces[i]->iGLSurface->bIsActive)
						DrawSurface(*vglSurfaces[i]->iGLSurface, *voCameras[vglSurfaces[i]->iGLSurface->uiCameraIndex]->iCamera);
					break;
				}
				case CameraUnion::FLOAT:
				{
					if (vglSurfaces[i]->iGLSurface->bIsActive)
						DrawSurface(*vglSurfaces[i]->iGLSurface, *voCameras[vglSurfaces[i]->iGLSurface->uiCameraIndex]->fCamera);
					break;
				}
				}
				break;
			}
			case SurfaceUnion::FLOAT:
			{
				switch (voCameras[vglSurfaces[i]->fGLSurface->uiCameraIndex]->Tag)
				{
				case CameraUnion::INT:
				{
					if (vglSurfaces[i]->fGLSurface->bIsActive)
						DrawSurface(*vglSurfaces[i]->fGLSurface, *voCameras[vglSurfaces[i]->fGLSurface->uiCameraIndex]->iCamera);
					break;
				}
				case CameraUnion::FLOAT:
				{
					if (vglSurfaces[i]->fGLSurface->bIsActive)
						DrawSurface(*vglSurfaces[i]->fGLSurface, *voCameras[vglSurfaces[i]->fGLSurface->uiCameraIndex]->fCamera);
					break;
				}
				}
				break;
			}
			}
		}
	}
	template <typename T, typename U>
	void DrawSurface(const GLSurface<T>& ac_glSurface, Camera<U>& a_Camera)
	{
		System::Point2D<T> Pos = ac_glSurface.Pos;// +a_Camera.GetScreenPos() - (a_Camera.GetWorldPos() - (a_Camera.GetDimensions() / 2));
		Pos.X += a_Camera.GetScreenPos().X - (a_Camera.GetWorldPos().X - a_Camera.GetDimensions().W / 2);
		Pos.Y += a_Camera.GetScreenPos().Y - (a_Camera.GetWorldPos().Y - a_Camera.GetDimensions().H / 2);

		glPushMatrix(); // Save the current matrix.

		glScalef(ac_glSurface.Scale.W, ac_glSurface.Scale.H, 0.0f);
		glTranslatef(Pos.X, Pos.Y, 0.0f);
		glRotatef(ac_glSurface.Rotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(
			-Pos.X - (ac_glSurface.Center.X - ac_glSurface.OffsetD.W / 2),
			-Pos.Y - (ac_glSurface.Center.Y - ac_glSurface.OffsetD.H / 2), 0.0f);

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);

		glBegin(GL_QUADS);
		{ // Just to make the code look nicer. Unnecessary
			glColor4ub(ac_glSurface.Color.Red, ac_glSurface.Color.Green, ac_glSurface.Color.Blue, ac_glSurface.Color.Alpha);

			// Bottom-left vertex (corner)
			glTexCoord2f(
				ac_glSurface.OffsetP.X / ac_glSurface.Dimensions.W,	// Position on texture to begin interpolation
				ac_glSurface.OffsetP.Y / ac_glSurface.Dimensions.H);
			glVertex2f(
				Pos.X - (ac_glSurface.OffsetD.W / 2),	// Vertex Coords
				Pos.Y - (ac_glSurface.OffsetD.H / 2));

			// Bottom-right vertex (corner)
			glTexCoord2f(
				(ac_glSurface.OffsetP.X / ac_glSurface.Dimensions.W) + (ac_glSurface.OffsetD.W / ac_glSurface.Dimensions.W),
				ac_glSurface.OffsetP.Y / ac_glSurface.Dimensions.H);
			glVertex2f(
				Pos.X + (ac_glSurface.OffsetD.W / 2),
				Pos.Y - (ac_glSurface.OffsetD.H / 2));

			// Top-right vertex (corner)
			glTexCoord2f(
				(ac_glSurface.OffsetP.X / ac_glSurface.Dimensions.W) + (ac_glSurface.OffsetD.W / ac_glSurface.Dimensions.W),
				(ac_glSurface.OffsetP.Y / ac_glSurface.Dimensions.H) + (ac_glSurface.OffsetD.H / ac_glSurface.Dimensions.H));
			glVertex2f(
				Pos.X + (ac_glSurface.OffsetD.W / 2),
				Pos.Y + (ac_glSurface.OffsetD.H / 2));

			// Top-left vertex (corner)
			glTexCoord2f(
				ac_glSurface.OffsetP.X / ac_glSurface.Dimensions.W,
				(ac_glSurface.OffsetP.Y / ac_glSurface.Dimensions.H) + (ac_glSurface.OffsetD.H / ac_glSurface.Dimensions.H));
			glVertex2f(
				Pos.X - (ac_glSurface.OffsetD.W / 2),
				Pos.Y + (ac_glSurface.OffsetD.H / 2));
		} // Just to make the code look nicer. Unnecessary
		glEnd();

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}

	void ReOrder()
	{
		for (int i = 0; i < vglSurfaces.size(); ++i)
		{
			switch (vglSurfaces[i]->Tag)
			{
			case SurfaceUnion::INT:
			{
				switch (voCameras[vglSurfaces[i]->iGLSurface->uiCameraIndex]->Tag)
				{
				case CameraUnion::INT:   IsInCamera(*vglSurfaces[i]->iGLSurface, *voCameras[vglSurfaces[i]->iGLSurface->uiCameraIndex]->iCamera); break;
				case CameraUnion::FLOAT: IsInCamera(*vglSurfaces[i]->iGLSurface, *voCameras[vglSurfaces[i]->iGLSurface->uiCameraIndex]->fCamera); break;
				}
				break;
			}
			case SurfaceUnion::FLOAT:
			{
				switch (voCameras[vglSurfaces[i]->fGLSurface->uiCameraIndex]->Tag)
				{
				case CameraUnion::INT:   IsInCamera(*vglSurfaces[i]->fGLSurface, *voCameras[vglSurfaces[i]->fGLSurface->uiCameraIndex]->iCamera); break;
				case CameraUnion::FLOAT: IsInCamera(*vglSurfaces[i]->fGLSurface, *voCameras[vglSurfaces[i]->fGLSurface->uiCameraIndex]->fCamera); break;
				}
				break;
			}
			}
		}
	}
	template <typename T, typename U>
	void IsInCamera(const GLSurface<T>& ac_glSurface, const Camera<U>& ac_Camera)
	{
		/*if ((ac_glSurface.Pos.X - ac_glSurface.OffsetD.W / 2 <= ac_Camera.m_WorldPos->X - ac_Camera.m_Dimensions.W) &&
			(ac_glSurface.Pos.X - ac_glSurface.))*/

	}

	void PushSurface(GLSurface<int>* a_glSurface)
	{
		SurfaceUnion* newSurface = new SurfaceUnion;

		newSurface->Tag = SurfaceUnion::INT;
		newSurface->iGLSurface = a_glSurface;

		vglSurfaces.push_back(newSurface);
	}
	void PushSurface(GLSurface<float>* a_glSurface)
	{
		SurfaceUnion* newSurface = new SurfaceUnion;

		newSurface->Tag = SurfaceUnion::FLOAT;
		newSurface->fGLSurface = a_glSurface;

		vglSurfaces.push_back(newSurface);
	}
	void Flip()
	{
		for (int i = 0; i < voWindows.size(); ++i)
			voWindows[i]->Flip();
	}

	void Quit()
	{
		voWindows.clear();
	}
}
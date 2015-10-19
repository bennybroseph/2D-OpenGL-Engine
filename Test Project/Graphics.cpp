#include "Graphics.h"



namespace Graphics
{
	std::vector<SDL_DisplayMode> sdlDisplayMode;
	SDL_GLContext glContext = nullptr;
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

		for (int i = 0; i < uiNumDisplays; ++i)
		{
			SDL_DisplayMode sdlTemp;
			if (SDL_GetDisplayMode(i, i, &sdlTemp) != 0)
				printf("SDL_GetDisplayMode failed: %s", SDL_GetError());
			else
				sdlDisplayMode.push_back(sdlTemp);
		}

		return 0;
	}

	void NewWindow(
		const System::Size2D<unsigned int>& ac_iResolution,
		const bool							ac_bFullscreen,
		const System::Size2D<unsigned int>& ac_iDimensions,
		const char*							ac_szTitle,
		const unsigned int					ac_uiMonitorIndex)
	{
		voWindows.push_back(new Window(
			ac_iResolution,
			ac_bFullscreen,
			ac_iDimensions,
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
		}
	}

	void NewCamera(
		const System::Point2D<int>&	   ac_iScreenPos,
		const System::Point2D<int>&	   ac_iWorldPos,
		const System::Point2D<int>&	   ac_iRelativePos,
		const System::Size2D<int>&	   ac_iDimensions,
		const System::Size2D<int>&	   ac_iZoom,
		const int					   ac_iRotation,
		const bool					   ac_bIsScrolling,
		const System::AngularVel<int>& ac_iVelocity,
		const unsigned int			   ac_uiWindowIndex,
		const unsigned int			   ac_uiWorldSpace)
	{
		CameraUnion* newCamera = new CameraUnion;

		System::Size2D<int> iSizeOffset = { ac_iDimensions.W * (int)voWindows[ac_uiWindowIndex]->GetDimensions().W / 100, ac_iDimensions.H * (int)voWindows[ac_uiWindowIndex]->GetDimensions().H / 100 };
		System::Point2D<int> iScreenOffset = {
			ac_iScreenPos.X * (int(voWindows[ac_uiWindowIndex]->GetDimensions().W) - iSizeOffset.W) / 100,
			abs(ac_iScreenPos.Y - 100) * (int(voWindows[ac_uiWindowIndex]->GetDimensions().H) - iSizeOffset.H) / 100 };

		System::Size2D<int> iResolution = { 
			(int)voWindows[ac_uiWindowIndex]->GetResolution().W * ((float)iSizeOffset.W / (float)voWindows[ac_uiWindowIndex]->GetDimensions().W),
			(int)voWindows[ac_uiWindowIndex]->GetResolution().H * ((float)iSizeOffset.H / (float)voWindows[ac_uiWindowIndex]->GetDimensions().H) };

		newCamera->Tag = CameraUnion::INT;
		newCamera->iCamera = new Camera<int>(iScreenOffset, ac_iWorldPos, ac_iRelativePos, iSizeOffset, iResolution, ac_iZoom, ac_iRotation, ac_bIsScrolling, ac_iVelocity, ac_uiWindowIndex, ac_uiWorldSpace);
		voCameras.push_back(newCamera);
	}
	void NewCamera(
		const System::Point2D<float>&	 ac_fScreenPos,
		const System::Point2D<float>&	 ac_fWorldPos,
		const System::Point2D<float>&	 ac_fRelativePos,
		const System::Size2D<float>&	 ac_fDimensions,
		const System::Size2D<float>&	 ac_fZoom,
		const float						 ac_fRotation,
		const bool						 ac_bIsScrolling,
		const System::AngularVel<float>& ac_fVelocity,
		const unsigned int				 ac_uiWindowIndex,
		const unsigned int			     ac_uiWorldSpace)
	{
		CameraUnion* newCamera = new CameraUnion;

		System::Size2D<float> fSizeOffset = { ac_fDimensions.W * voWindows[ac_uiWindowIndex]->GetDimensions().W , ac_fDimensions.H * voWindows[ac_uiWindowIndex]->GetDimensions().H };
		System::Point2D<float> fScreenOffset = {
			ac_fScreenPos.X * (voWindows[ac_uiWindowIndex]->GetDimensions().W - fSizeOffset.W),
			abs(ac_fScreenPos.Y - 1) * (voWindows[ac_uiWindowIndex]->GetDimensions().H - fSizeOffset.H) };

		System::Size2D<float> fResolution;

		newCamera->Tag = CameraUnion::FLOAT;
		newCamera->fCamera = new Camera<float>(fScreenOffset, ac_fWorldPos, ac_fRelativePos, fSizeOffset, fResolution, ac_fZoom, ac_fRotation, ac_bIsScrolling, ac_fVelocity, ac_uiWindowIndex, ac_uiWorldSpace);
		voCameras.push_back(newCamera);
	}

	void Draw()
	{
		for (int i = 0; i < voCameras.size(); ++i)
		{
			switch (voCameras[i]->Tag)
			{
			case CameraUnion::INT:	 UpdateCameras(*voCameras[i]->iCamera);
			case CameraUnion::FLOAT: UpdateCameras(*voCameras[i]->fCamera);
			}
		}
	}

	template <typename T>
	void UpdateCameras(Camera<T> a_Camera)
	{
		a_Camera.Update();

		SDL_GL_MakeCurrent(voWindows[a_Camera.GetWindowIndex()]->GetWindow(), glContext);

		glViewport(
			a_Camera.GetScreenPos().X,
			a_Camera.GetScreenPos().Y,
			a_Camera.GetDimensions().W,
			a_Camera.GetDimensions().H);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(
			0.0f,
			a_Camera.GetResolution().W,
			a_Camera.GetResolution().H,
			0.0f, -1.0f, 1.0f);

		for (int i = 0; i < vglSurfaces.size(); ++i)
		{
			switch (vglSurfaces[i]->Tag)
			{
			case SurfaceUnion::INT:
			{
				if (vglSurfaces[i]->iGLSurface->bIsActive && a_Camera.GetWorldSpace() == vglSurfaces[i]->iGLSurface->uiWorldSpace)
				{
					DrawSurface(*vglSurfaces[i]->iGLSurface, a_Camera);
				}
				break;
			}
			case SurfaceUnion::FLOAT:
			{
				if (vglSurfaces[i]->fGLSurface->bIsActive && a_Camera.GetWorldSpace() == vglSurfaces[i]->fGLSurface->uiWorldSpace)
				{
					DrawSurface(*vglSurfaces[i]->fGLSurface, a_Camera);
				}
				break;
			}
			}
		}
	}

	template <typename T, typename U>
	void DrawSurface(const GLSurface<T>& ac_glSurface, Camera<U>& a_Camera)
	{
		glPushMatrix(); // Save the current matrix.

		glTranslatef(
			ac_glSurface.Pos.X + (ac_glSurface.Center.X - ac_glSurface.OffsetD.W / 2),
			ac_glSurface.Pos.Y + (ac_glSurface.Center.Y - ac_glSurface.OffsetD.H / 2),
			0.0f);
		glScalef(ac_glSurface.Scale.W, ac_glSurface.Scale.H, 0.0f);
		glRotatef(ac_glSurface.Rotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(
			-ac_glSurface.Pos.X - (ac_glSurface.Center.X - ac_glSurface.OffsetD.W / 2),
			-ac_glSurface.Pos.Y - (ac_glSurface.Center.Y - ac_glSurface.OffsetD.H / 2), 0.0f);

		glTranslatef(a_Camera.GetResolution().W / 2, a_Camera.GetResolution().H / 2, 0.0f);
		glScalef(a_Camera.GetZoom().W, a_Camera.GetZoom().H, 0.0f);
		glRotatef(a_Camera.GetRotation(), 0.0f, 0.0f, 1.0f);
		glTranslatef(
			-a_Camera.GetWorldPos().X,
			-a_Camera.GetWorldPos().Y, 0.0f);

		GLfloat glVertices[] = {
			(float)ac_glSurface.OffsetP.X / (float)ac_glSurface.Dimensions.W,
			(float)ac_glSurface.OffsetP.Y / (float)ac_glSurface.Dimensions.H,

			((float)ac_glSurface.OffsetP.X / (float)ac_glSurface.Dimensions.W) + ((float)ac_glSurface.OffsetD.W / (float)ac_glSurface.Dimensions.W),
			(float)ac_glSurface.OffsetP.Y / (float)ac_glSurface.Dimensions.H,

			((float)ac_glSurface.OffsetP.X / (float)ac_glSurface.Dimensions.W) + ((float)ac_glSurface.OffsetD.W / (float)ac_glSurface.Dimensions.W),
			((float)ac_glSurface.OffsetP.Y / (float)ac_glSurface.Dimensions.H) + ((float)ac_glSurface.OffsetD.H / (float)ac_glSurface.Dimensions.H),

			(float)ac_glSurface.OffsetP.X / (float)ac_glSurface.Dimensions.W,
			((float)ac_glSurface.OffsetP.Y / (float)ac_glSurface.Dimensions.H) + ((float)ac_glSurface.OffsetD.H / (float)ac_glSurface.Dimensions.H)
		};

		GLfloat glPosition[] = {
			ac_glSurface.Pos.X - (ac_glSurface.OffsetD.W / 2),
			ac_glSurface.Pos.Y - (ac_glSurface.OffsetD.H / 2),

			ac_glSurface.Pos.X + (ac_glSurface.OffsetD.W / 2),
			ac_glSurface.Pos.Y - (ac_glSurface.OffsetD.H / 2),

			ac_glSurface.Pos.X + (ac_glSurface.OffsetD.W / 2),
			ac_glSurface.Pos.Y + (ac_glSurface.OffsetD.H / 2),

			ac_glSurface.Pos.X - (ac_glSurface.OffsetD.W / 2),
			ac_glSurface.Pos.Y + (ac_glSurface.OffsetD.H / 2)
		};

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);
		glColor4ub(ac_glSurface.Color.Red, ac_glSurface.Color.Green, ac_glSurface.Color.Blue, ac_glSurface.Color.Alpha);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, glVertices);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, glPosition);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}

	bool SortLayer(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight)
	{
		switch (ac_pglLeft->Tag)
		{
		case SurfaceUnion::INT:
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
		case SurfaceUnion::FLOAT:
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
		}

		return false;
	}
	bool SortCamera(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight)
	{
		switch (ac_pglLeft->Tag)
		{
		case SurfaceUnion::INT:
			switch (ac_pglRight->Tag)
			{
			case SurfaceUnion::INT:	  return ac_pglLeft->iGLSurface->uiWorldSpace < ac_pglRight->iGLSurface->uiWorldSpace; break;
			case SurfaceUnion::FLOAT: return ac_pglLeft->iGLSurface->uiWorldSpace < ac_pglRight->fGLSurface->uiWorldSpace; break;
			}
		case SurfaceUnion::FLOAT:
			switch (ac_pglRight->Tag)
			{
			case SurfaceUnion::INT:	  return ac_pglLeft->fGLSurface->uiWorldSpace < ac_pglRight->iGLSurface->uiWorldSpace; break;
			case SurfaceUnion::FLOAT: return ac_pglLeft->fGLSurface->uiWorldSpace < ac_pglRight->fGLSurface->uiWorldSpace; break;
			}
		}
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

	void Draw_Rect(
		const float ac_fPosX, const float ac_fPosY,
		const float ac_fWidth, const float ac_fHeight,
		const int ac_iRed, const int ac_iGreen, const int ac_iBlue)
	{
		glBindTexture(GL_TEXTURE_2D, NULL);// boundTexture = NULL; }

		glBegin(GL_QUADS);
		glColor3ub(ac_iRed, ac_iGreen, ac_iBlue);
		//Bottom-left vertex (corner)
		glVertex3f(ac_fPosX, ac_fPosY, 0.0f); //Vertex Coords

											  //Bottom-right vertex (corner)
		glVertex3f(ac_fPosX + ac_fWidth, ac_fPosY, 0.f);

		//Top-right vertex (corner)
		glVertex3f(ac_fPosX + ac_fWidth, ac_fPosY + ac_fHeight, 0.f);

		//Top-left vertex (corner)
		glVertex3f(ac_fPosX, ac_fPosY + ac_fHeight, 0.f);

		glEnd();
	}

	void Flip()
	{
		for (int i = 0; i < voWindows.size(); ++i)
		{
			SDL_GL_MakeCurrent(voWindows[i]->GetWindow(), glContext);
			voWindows[i]->Flip();
		}
	}

	void Quit()
	{
		voWindows.clear();
	}
}
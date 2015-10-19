#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Window.h"
#include "Camera.h"
#include "TileMap.h"

#include <algorithm>

#include <SDL_image.h>

namespace Graphics
{
	struct SurfaceUnion
	{
		enum { INT, FLOAT }Tag;
		union
		{
			GLSurface<int>*	  iGLSurface;
			GLSurface<float>* fGLSurface;
		};
	};
	extern std::vector<SurfaceUnion*> vglSurfaces;

	struct CameraUnion
	{
		enum { INT , FLOAT }Tag;
		union
		{
			Camera<int>*   iCamera;
			Camera<float>* fCamera;
		};
	};

	bool Init();

	void NewWindow(
		const System::Size2D<unsigned int> &ac_iResolution,		// The window's internal resolution
		const bool ac_bFullscreen,								// Whether or not the window should be full screen on creation
		const System::Size2D<unsigned int> &ac_iDimensions,		// The window's width and height
		const char *ac_szTitle,									// The window's title
		const unsigned int ac_uiMonitorIndex);					// Which monitor the window should be created on

	void NewCamera(
		const System::Point2D<int>&	   ac_iScreenPos,
		const System::Point2D<int>&	   ac_iWorldPos,
		const System::Point2D<int>&	   ac_iRelativePos,
		const System::Size2D<int>&	   ac_iDimensions,
		const bool					   ac_bIsScrolling,
		const System::AngularVel<int>& ac_iVelocity,
		const unsigned int			   ac_uiWindowIndex,
		const unsigned int			   ac_uiWorldSpace);
	void NewCamera(
		const System::Point2D<float>&	 ac_fScreenPos,
		const System::Point2D<float>&	 ac_fWorldPos,
		const System::Point2D<float>&	 ac_fRelativePos,
		const System::Size2D<float>&	 ac_fDimensions,
		const bool						 ac_bIsScrolling,
		const System::AngularVel<float>& ac_fVelocity,
		const unsigned int				 ac_uiWindowIndex,
		const unsigned int			     ac_uiWorldSpace);

	// - Draws all surfaces currently in the 'vglSurfaces' vector
	void Draw();

	template <typename T>
	void UpdateCameras(Camera<T> a_Camera);

	template <typename T, typename U>
	void DrawSurface(const GLSurface<T>& ac_glSurface, Camera<U>& a_Camera);

	bool SortLayer(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight);
	bool SortCamera(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight);

	template <typename T>
	GLSurface<T>* LoadSurface(const char* ac_szFilename);
	template <typename T>
	GLSurface<T>* LoadSurface(SDL_Surface& a_sdlSurface);

	void PushSurface(GLSurface<int>* a_glSurface);
	void PushSurface(GLSurface<float>* a_glSurface);

	void Draw_Rect(
		const float ac_fPosX, const float ac_fPosY,
		const float ac_fWidth, const float ac_fHeight,
		const int ac_iRed, const int ac_iGreen, const int ac_iBlue);

	void Flip(); // Clears the buffer of all windows to allow all the new information to be displayed

	void Quit();
}

namespace Graphics
{
	template <typename T>
	GLSurface<T>* LoadSurface(const char* ac_szFilename)
	{
		SDL_Surface* sdlSurface;

		sdlSurface = IMG_Load(ac_szFilename);
		if (sdlSurface == NULL)
		{
			printf("SDL_Error: %s\n", SDL_GetError());

			GLSurface<T> *glSurface = nullptr;
			return glSurface;
		}

		return LoadSurface<T>(*sdlSurface);
	}
	template <typename T>
	GLSurface<T>* LoadSurface(SDL_Surface& a_sdlSurface)
	{
		GLSurface<T>* glSurface = new GLSurface<T>;

		glGenTextures(1, &glSurface->Surface);
		glBindTexture(GL_TEXTURE_2D, glSurface->Surface);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_sdlSurface.w, a_sdlSurface.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_sdlSurface.pixels);

		glSurface->Pos = { NULL, NULL };
		glSurface->OffsetP = { NULL, NULL };

		glSurface->Dimensions.W = a_sdlSurface.w;
		glSurface->Dimensions.H = a_sdlSurface.h;

		glSurface->Center.X = glSurface->Dimensions.W / 2.0f;
		glSurface->Center.Y = glSurface->Dimensions.H / 2.0f;

		glSurface->OffsetD.W = glSurface->Dimensions.W;
		glSurface->OffsetD.H = glSurface->Dimensions.H;

		glSurface->Rotation = NULL;
		glSurface->Scale = { 1, 1 };

		glSurface->Color = { 255, 255, 255, 255 };

		glSurface->Layer = LayerType::BACKGROUND;

		glSurface->uiWorldSpace = 0;

		glSurface->bIsActive = true;

		SDL_FreeSurface(&a_sdlSurface);

		PushSurface(glSurface);
		std::sort(vglSurfaces.begin(), vglSurfaces.end(), SortCamera);
		std::sort(vglSurfaces.begin(), vglSurfaces.end(), SortLayer);

		return glSurface;
	}
}
#endif // _GRAPHICS_H_

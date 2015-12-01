////////////////////////////////////////////////////////////
// File: GLSurface.h
// Author: Ben Odom
// Date Created: 11/10/2015
////////////////////////////////////////////////////////////

#ifndef _GLSURFACE_H_
#define _GLSURFACE_H_

#include "System.h"

#include "SDL_image.h"
#include "glfw3.h"

#include <vector>

namespace Graphics
{
	enum LayerType
	{
		BACKGROUND,
		MIDGROUND,
		FOREGROUND,

		FOUNDATION,
		STRUCTURE,
		OVERLAY,

		ALWAYS_TOP
	};

	template <typename T>
	struct GLSurface
	{
		GLuint Surface;

		System::Point2D<T> Pos;
		System::Point2D<T> OffsetPos;
		System::Point2D<T> Center;

		System::Size2D<T> Size;
		System::Size2D<T> OffsetSize;
		System::Size2D<T> Scale;
		T Rotation;

		System::Color<T> Color;

		LayerType Layer;

		unsigned int uiWorldSpace;

		bool bIsActive;
	};

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

	// - Loads a 'GLSurface' from a filename
	template <typename T = int>
	GLSurface<T>* LoadSurface(const char* ac_szFilename);
	// - Loads a 'GLSurface' from an existing 'SDL_Surface'
	template <typename T = int>
	GLSurface<T>* LoadSurface(SDL_Surface& a_sdlSurface);
	template <typename T = int>
	void ReloadSurface(GLSurface<T>* a_glSurface, SDL_Surface& a_sdlSurface);

	// - Pushes a 'GLSurface' of type int into the 'vglSurfaces' vector
	void PushSurface(GLSurface<int>* a_glSurface);
	// - Pushes a 'GLSurface' of type float into the 'vglSurfaces' vector
	void PushSurface(GLSurface<float>* a_glSurface);

	// - Draws a 'GLSurface' in relation to a 'Camera' object
	template <typename T>
	void ManipulateSurface(const GLSurface<T>& ac_glSurface);
	template <typename T>
	void DrawSurface(const GLSurface<T>& ac_glSurface);

	// Determines which Surface out of the vector needs to be deleted
	template <typename T>
	void DeleteSurface(GLSurface<T>* a_pglSurface);
	// Takes the parsed surface and deletes it from memory as well as erases it from the vector
	template <typename T>
	void DeleteSurface(GLSurface<T>* a_pglSurface, GLSurface<T>* a_pglDeleteSurface, const unsigned int ac_uiIndex);
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

		ReloadSurface(glSurface, a_sdlSurface);

		glSurface->Pos = { NULL, NULL };
		glSurface->OffsetPos = { NULL, NULL };

		glSurface->Size.W = a_sdlSurface.w;
		glSurface->Size.H = a_sdlSurface.h;

		glSurface->Center.X = glSurface->Size.W / (T)2.0f;
		glSurface->Center.Y = glSurface->Size.H / (T)2.0f;

		glSurface->OffsetSize.W = glSurface->Size.W;
		glSurface->OffsetSize.H = glSurface->Size.H;

		glSurface->Rotation = NULL;
		glSurface->Scale = { 1, 1 };

		glSurface->Color = { 255, 255, 255, 255 };

		glSurface->Layer = LayerType::BACKGROUND;

		glSurface->uiWorldSpace = 0;

		glSurface->bIsActive = true;

		SDL_FreeSurface(&a_sdlSurface);

		PushSurface(glSurface);

		return glSurface;
	}
	template <typename T>
	void ReloadSurface(GLSurface<T>* a_glSurface, SDL_Surface& a_sdlSurface)
	{
		glDeleteTextures(1, &a_glSurface->Surface);

		glGenTextures(1, &a_glSurface->Surface);
		glBindTexture(GL_TEXTURE_2D, a_glSurface->Surface);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_sdlSurface.w, a_sdlSurface.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_sdlSurface.pixels);
	}

	template <typename T>
	void ManipulateSurface(const GLSurface<T>& ac_glSurface)
	{
		GLfloat glMatrix[16];

		if (ac_glSurface.Layer == LayerType::OVERLAY)
		{
			glGetFloatv(GL_MODELVIEW_MATRIX, glMatrix);
			glPopMatrix();
		}

		glPushMatrix(); // Save the current matrix.

		glTranslatef(																	// Move the image back to its original position
			(GLfloat)(ac_glSurface.Pos.X + (ac_glSurface.Center.X - ac_glSurface.OffsetSize.W / 2)),
			(GLfloat)(ac_glSurface.Pos.Y + (ac_glSurface.Center.Y - ac_glSurface.OffsetSize.H / 2)),
			0.0f);
		glScalef((GLfloat)ac_glSurface.Scale.W, (GLfloat)ac_glSurface.Scale.H, 0.0f);						// Scale the image
		glRotatef((GLfloat)ac_glSurface.Rotation, 0.0f, 0.0f, 1.0f);								// Rotate the image
		glTranslatef(																	// Move the image to (0,0) on the screen
			(GLfloat)(-ac_glSurface.Pos.X - (ac_glSurface.Center.X - ac_glSurface.OffsetSize.W / 2)),
			(GLfloat)(-ac_glSurface.Pos.Y - (ac_glSurface.Center.Y - ac_glSurface.OffsetSize.H / 2)), 0.0f);

		DrawSurface(ac_glSurface);

		if (ac_glSurface.Layer == LayerType::OVERLAY)
			glLoadMatrixf(glMatrix);
		else
			glPopMatrix(); // Reset the current matrix to the one that was saved.
	}
	template <typename T>
	void DrawSurface(const GLSurface<T>& ac_glSurface)
	{
		GLfloat glVertices[] = {
			(float)ac_glSurface.OffsetPos.X / (float)ac_glSurface.Size.W,
			(float)ac_glSurface.OffsetPos.Y / (float)ac_glSurface.Size.H,

			((float)ac_glSurface.OffsetPos.X / (float)ac_glSurface.Size.W) + ((float)ac_glSurface.OffsetSize.W / (float)ac_glSurface.Size.W),
			(float)ac_glSurface.OffsetPos.Y / (float)ac_glSurface.Size.H,

			((float)ac_glSurface.OffsetPos.X / (float)ac_glSurface.Size.W) + ((float)ac_glSurface.OffsetSize.W / (float)ac_glSurface.Size.W),
			((float)ac_glSurface.OffsetPos.Y / (float)ac_glSurface.Size.H) + ((float)ac_glSurface.OffsetSize.H / (float)ac_glSurface.Size.H),

			(float)ac_glSurface.OffsetPos.X / (float)ac_glSurface.Size.W,
			((float)ac_glSurface.OffsetPos.Y / (float)ac_glSurface.Size.H) + ((float)ac_glSurface.OffsetSize.H / (float)ac_glSurface.Size.H)
		};

		GLfloat glPosition[] = {
			(GLfloat)(ac_glSurface.Pos.X - (ac_glSurface.OffsetSize.W / 2)),
			(GLfloat)(ac_glSurface.Pos.Y - (ac_glSurface.OffsetSize.H / 2)),

			(GLfloat)(ac_glSurface.Pos.X + (ac_glSurface.OffsetSize.W / 2)),
			(GLfloat)(ac_glSurface.Pos.Y - (ac_glSurface.OffsetSize.H / 2)),

			(GLfloat)(ac_glSurface.Pos.X + (ac_glSurface.OffsetSize.W / 2)),
			(GLfloat)(ac_glSurface.Pos.Y + (ac_glSurface.OffsetSize.H / 2)),

			(GLfloat)(ac_glSurface.Pos.X - (ac_glSurface.OffsetSize.W / 2)),
			(GLfloat)(ac_glSurface.Pos.Y + (ac_glSurface.OffsetSize.H / 2))
		};

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);
		glColor4ub((GLubyte)ac_glSurface.Color.Red, (GLubyte)ac_glSurface.Color.Green, (GLubyte)ac_glSurface.Color.Blue, (GLubyte)ac_glSurface.Color.Alpha);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, glVertices);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, glPosition);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	template <typename T>
	void DeleteSurface(GLSurface<T>* a_pglSurface)
	{
		for (unsigned int i = 0; i < vglSurfaces.size(); ++i)
		{
			switch (vglSurfaces[i]->Tag)
			{
			case SurfaceUnion::INT: DeleteSurface(vglSurfaces[i]->iGLSurface, a_pglSurface, i); break;
			case SurfaceUnion::FLOAT: DeleteSurface(vglSurfaces[i]->fGLSurface, a_pglSurface, i); break;
			}
		}
	}
	template <typename T>
	void DeleteSurface(GLSurface<T>* a_pglSurface, GLSurface<T>* a_pglDeleteSurface, const unsigned int ac_uiIndex)
	{
		if (a_pglSurface == a_pglSurface)
		{
			GLSurface<T>* DeleteSurface = a_pglDeleteSurface;
			vglSurfaces.erase(vglSurfaces.begin() + ac_uiIndex);
			glDeleteTextures(1, &DeleteSurface->Surface);
			delete DeleteSurface;
		}
	}
}

#endif // _GLSURFACE_H_
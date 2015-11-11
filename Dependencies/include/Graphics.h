#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Window.h"
#include "Camera.h"
#include "GLSurface.h"

#include <algorithm>

namespace Graphics
{
	// - Sets up the Graphics namespace to be used. Must be called before using any free functions
	bool Init();

	// - Allows a window in the 'voWindows' vector to change Size
	void Resize(
		const System::Size2D<unsigned int>& ac_uiNewDimensions,		// The new Size of the Window
		const unsigned int					ac_uiNewMonitorIndex,	// The monitor the Window should be placed on
		const unsigned int					ac_uiIndex);			// Which window to change

																	// - Toggles the window from it's current state of full screen
	void ToggleFullscreen(const unsigned int ac_uiIndex);

	// - Draws all surfaces currently in the 'vglSurfaces' vector
	void Draw();

	// - Updates the view-port to match the current 'Camera' object used to draw and then draws all surfaces in its world space
	template <typename T>
	void UpdateCameras(Camera<T>& a_Camera);

	void Sort();
	// - Sorts each surface based on its layer order
	bool SortLayer(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight);
	// - Sorts each surface based on its camera order
	bool SortCamera(SurfaceUnion* ac_pglLeft, SurfaceUnion* ac_pglRight);

	// - Draws a colored rectangle at the specified position with a given width and height
	template <typename T = float>
	void DrawRect(const System::Point2D<T>& ac_Pos, const System::Size2D<T>& ac_Size, const System::Color<T>& ac_Color);
	// - Draws a colored line at with a given beginning and end
	template <typename T = float>
	void DrawLine(const System::Point2D<T>& ac_Begin, const System::Point2D<T>& ac_End, const System::Color<T>& ac_Color);
	// - Draws a colored pixel with a given beginning and end
	template <typename T = float>
	void DrawPoint(const System::Point2D<T>& ac_Pos, const System::Color<T>& ac_Color);
	// - Draws a colored ring with a given center, radius, and quality modifier
	template <typename T = float>
	void DrawRing(const System::Point2D<T> ac_Center, const T ac_Radius, const T ac_Quality, const System::Color<T>& ac_Color);
	// - Draws a colored circle with a given center, radius, and quality modifier
	template <typename T>
	void DrawCircle(const System::Point2D<T> ac_Center, const T ac_Radius, const T ac_Quality, const System::Color<T>& ac_Color);

	void Flip(); // Clears the buffer of all windows to allow all the new information to be displayed

	void Quit();
}

// All templated functions that need to be called outside of the namespace go here
namespace Graphics
{
	template <typename T>
	void DrawRect(const System::Point2D<T>& ac_Pos, const System::Size2D<T>& ac_Size, const System::Color<T>& ac_Color)
	{
		glPushMatrix(); // Save the current matrix.

		glBindTexture(GL_TEXTURE_2D, NULL);

		glColor4ub(ac_Color.Red, ac_Color.Green, ac_Color.Blue, ac_Color.Alpha);
		glBegin(GL_QUADS);
		{
			//Bottom-left vertex (corner)
			glVertex3f(ac_Pos.X, ac_Pos.Y, 0.0f); //Vertex Coords

												  //Bottom-right vertex (corner)
			glVertex3f(ac_Pos.X + ac_Size.W, ac_Pos.Y, 0.f);

			//Top-right vertex (corner)
			glVertex3f(ac_Pos.X + ac_Size.W, ac_Pos.Y + ac_Size.H, 0.f);

			//Top-left vertex (corner)
			glVertex3f(ac_Pos.X, ac_Pos.Y + ac_Size.H, 0.f);
		}
		glEnd();

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}
	template <typename T>
	void DrawLine(const System::Point2D<T>& ac_Begin, const System::Point2D<T>& ac_End, const System::Color<T>& ac_Color)
	{
		glPushMatrix(); // Save the current matrix.

		glBindTexture(GL_TEXTURE_2D, NULL);

		glColor4ub(ac_Color.Red, ac_Color.Green, ac_Color.Blue, ac_Color.Alpha);

		glBegin(GL_LINES);
		{
			glVertex2f(ac_Begin.X, ac_Begin.Y);
			glVertex2f(ac_End.X, ac_End.Y);
		}
		glEnd();

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}
	template <typename T>
	void DrawPoint(const System::Point2D<T>& ac_Pos, const System::Color<T>& ac_Color)
	{
		glPushMatrix(); // Save the current matrix.

		glBindTexture(GL_TEXTURE_2D, NULL);

		glColor4ub(ac_Color.Red, ac_Color.Green, ac_Color.Blue, ac_Color.Alpha);

		glBegin(GL_POINTS);
		glVertex2f(ac_Pos.X, ac_Pos.Y);
		glEnd();

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}
	template <typename T>
	void DrawRing(const System::Point2D<T> ac_Center, const T ac_Radius, const T ac_Quality, const System::Color<T>& ac_Color)
	{
		glPushMatrix(); // Save the current matrix.

		glBindTexture(GL_TEXTURE_2D, NULL);

		glColor4ub(ac_Color.Red, ac_Color.Green, ac_Color.Blue, ac_Color.Alpha);

		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i <= ac_Quality; ++i)
			{
				glVertex2f(
					ac_Center.X + cosf(i * (PI * 2) / ac_Quality)*ac_Radius,
					ac_Center.Y + sinf(i * (PI * 2) / ac_Quality)*ac_Radius);
			}
		}
		glEnd();

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}
	template <typename T>
	void DrawCircle(const System::Point2D<T> ac_Center, const T ac_Radius, const T ac_Quality, const System::Color<T>& ac_Color)
	{
		glPushMatrix(); // Save the current matrix.

		glBindTexture(GL_TEXTURE_2D, NULL);

		glColor4ub(ac_Color.Red, ac_Color.Green, ac_Color.Blue, ac_Color.Alpha);

		glBegin(GL_TRIANGLE_FAN);
		{
			glVertex2f(ac_Center.X, ac_Center.Y); // center of circle
			for (int i = 0; i <= ac_Quality; ++i)
			{
				glVertex2f(
					ac_Center.X + cosf(i * (PI * 2) / ac_Quality)*ac_Radius,
					ac_Center.Y + sinf(i * (PI * 2) / ac_Quality)*ac_Radius);
			}
		}
		glEnd();

		glPopMatrix(); // Reset the current matrix to the one that was saved.
	}
}
#endif // _GRAPHICS_H_

////////////////////////////////////////////////////////////
// File: GLSurface.h
// Author: Ben Odom
// Date Created: 11/10/2015
////////////////////////////////////////////////////////////

#include "GLSurface.h"

namespace Graphics
{
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
}
#ifndef _GLSPRITE_H_
#define _GLSPRITE_H_

#include "Graphics.h"

template <typename T = int>
class GLSprite
{
private:
	template <typename T = int>
	struct SpriteData
	{
		Graphics::GLSurface<T> glSurface;
		
		System::Size2D<T> Size;

		System::Point2D<T> Index;
	};

public:
	GLSprite();
	~GLSprite();
};

template <typename T>
GLSprite<T>::GLSprite()
{

}

template <typename T>
GLSprite<T>::~GLSprite()
{

}
#endif // _GLSPRITE_H_

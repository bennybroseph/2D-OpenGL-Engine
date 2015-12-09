#ifndef _GLSPRITE_H_
#define _GLSPRITE_H_

#include "Graphics.h"

template <typename T = int>
class GLSprite
{
private:
	Graphics::GLSurface<T>* m_glSurface;

	System::Size2D<T> m_Size;

	System::Point2D<int> m_iIndex;
	System::Point2D<int> m_iMaxIndex;

	float m_fAnimPerSec;

	int m_iPrevTime;

	bool m_bIsPaused;

public:
	void SetPos(const System::Point2D<T>& ac_Pos);

	void SetIndex(const System::Point2D<int>& ac_iIndex);
	void SetMaxIndex(const System::Point2D<int>& ac_iMaxIndex);

	void SetLayer(const Graphics::LayerType ac_LayerIndex);

	const System::Point2D<int>& GetIndex();

	void Update();

	void Pause();
	void Resume();

	GLSprite<T>::GLSprite(
		const char*					ac_szFilename,
		const System::Size2D<T>&	ac_Size,
		const System::Point2D<int>& ac_iIndex,
		const System::Point2D<int>& ac_iMaxIndex,
		const float					ac_fAnimPerSec);
	GLSprite();
	~GLSprite();
};

template <typename T>
void GLSprite<T>::SetPos(const System::Point2D<T>& ac_Pos)
{
	m_glSurface->Pos = ac_Pos;
}

template <typename T>
void GLSprite<T>::SetIndex(const System::Point2D<int>& ac_Index)
{
	m_iIndex = ac_Index;
}
template <typename T>
void GLSprite<T>::SetMaxIndex(const System::Point2D<int>& ac_iMaxIndex)
{
	m_iMaxIndex = ac_iMaxIndex;
}

template <typename T>
void GLSprite<T>::SetLayer(const Graphics::LayerType ac_LayerIndex)
{
	m_glSurface->Layer = ac_LayerIndex;
}

template <typename T>
const System::Point2D<int>& GLSprite<T>::GetIndex()
{
	return m_iIndex;
}

template <typename T>
void GLSprite<T>::Update()
{
	if (clock() - m_iPrevTime >= int(m_fAnimPerSec * 1000) && !m_bIsPaused)
	{
		m_iIndex.X += 1;

		m_iPrevTime = clock();
	}

	if (m_iIndex.X > m_iMaxIndex.X)
		m_iIndex.X = 0;

	m_glSurface->OffsetPos = m_iIndex * m_Size;
}

template <typename T>
void GLSprite<T>::Pause()
{
	m_bIsPaused = true;
}

template <typename T>
void GLSprite<T>::Resume()
{
	m_bIsPaused = false;
}


template <typename T = int>
GLSprite<T>::GLSprite(
	const char*					ac_szFilename,
	const System::Size2D<T>&	ac_Size,
	const System::Point2D<int>& ac_iIndex,
	const System::Point2D<int>& ac_iMaxIndex,
	const float					ac_fAnimPerSec)
{
	m_glSurface = Graphics::LoadSurface<T>(ac_szFilename);
	m_Size = ac_Size;
	m_iIndex = ac_iIndex;
	m_iMaxIndex = ac_iMaxIndex;
	m_fAnimPerSec = ac_fAnimPerSec;

	m_glSurface->Pos = { NULL, NULL };
	m_glSurface->OffsetSize = m_Size;
	m_glSurface->OffsetPos = m_iIndex * m_Size;
	m_glSurface->Center = { (m_Size.W / 2), (m_Size.H / 2) };
	//m_glSurface->Scale = { 3, 3 };

	m_iPrevTime = NULL;
}
template <typename T>
GLSprite<T>::GLSprite()
{
	m_glSurface->Pos = { NULL, NULL };
}

template <typename T>
GLSprite<T>::~GLSprite()
{

}
#endif // _GLSPRITE_H_

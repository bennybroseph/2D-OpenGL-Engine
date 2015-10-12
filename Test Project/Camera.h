#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "System.h"

namespace Graphics
{
	template <typename T>
	class Camera
	{
	private:
		System::Point2D<T>		  m_ScreenPos;
		System::Point2D<T>		  m_WorldPos;
		const System::Point2D<T>* m_RelativePos;

		System::Size2D<T> m_Dimensions;

		bool m_bIsScrolling;

		System::AngularVel<T> m_Velocity;

		unsigned int m_uiWindowIndex;

	public:
		void Resize(const System::Size2D<T>&  ac_NewDimensions);
		void RePosition(const System::Point2D<T>& ac_ScreenPos);
		void ReBind(const System::Point2D<T>& ac_NewRelativePos);

		void Update();

		const System::Point2D<T>& GetScreenPos();
		const System::Point2D<T>& GetWorldPos();
		const System::Size2D<T>& GetDimensions();

		Camera(
			const System::Point2D<T>&	 ac_ScreenPos,
			const System::Point2D<T>&	 ac_WorldPos,
			const System::Point2D<T>&	 ac_RelativePos,
			const System::Size2D<T>&	 ac_Dimension,
			const bool					 ac_bIsScrolling,
			const System::AngularVel<T>& ac_Velocity,
			const unsigned int			 ac_uiWindowIndex);
		Camera() = delete;
		~Camera();
	};

	template <typename T>
	void Camera<T>::Resize(const System::Size2D<T>& ac_NewDimensions)
	{
		m_fDimensions = ac_fNewDimensions;
	}
	template <typename T>
	void Camera<T>::RePosition(const System::Point2D<T>& ac_NewScreenPos)
	{
		m_fScreenPos = ac_NewScreenPos;
	}
	template <typename T>
	void Camera<T>::ReBind(const System::Point2D<T>& ac_NewRelativePos)
	{
		m_RelativePos = &ac_NewWorldPos;
	}

	template <typename T>
	void Camera<T>::Update()
	{
		if (m_bIsScrolling)
			m_WorldPos.X += 0.01;
			//m_WorldPos += m_Velocity;
	}

	template <typename T>
	const System::Point2D<T>& Camera<T>::GetScreenPos()
	{
		return m_ScreenPos;
	}
	template <typename T>
	const System::Point2D<T>& Camera<T>::GetWorldPos()
	{
		return m_WorldPos + *m_RelativePos;
	}
	template <typename T>
	const System::Size2D<T>& Camera<T>::GetDimensions()
	{
		return m_Dimensions;
	}


	template <typename T>
	Camera<T>::Camera(
		const System::Point2D<T>&	 ac_ScreenPos,
		const System::Point2D<T>&	 ac_WorldPos,
		const System::Point2D<T>&	 ac_RelativePos,
		const System::Size2D<T>&	 ac_Dimension,
		const bool					 ac_bIsScrolling,
		const System::AngularVel<T>& ac_Velocity,
		const unsigned int			 ac_uiWindowIndex)
	{
		m_ScreenPos =	 ac_ScreenPos;
		m_WorldPos =	 ac_WorldPos;
		m_RelativePos = &ac_RelativePos;

		m_Dimensions = ac_Dimension;

		m_bIsScrolling = ac_bIsScrolling;

		m_Velocity = ac_Velocity;

		m_uiWindowIndex = ac_uiWindowIndex;
	}
	template <typename T>
	Camera<T>::~Camera()
	{

	}
}

#endif // _CAMERA_H_
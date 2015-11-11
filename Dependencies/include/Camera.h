#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "System.h"

#include <vector>

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
		System::Size2D<T> m_Resolution;

		System::Size2D<T> m_Zoom;
		T m_Rotation;

		bool m_bIsScrolling;

		System::AngularVel<T> m_Velocity;

		unsigned int m_uiWindowIndex;
		unsigned int m_uiWorldSpace;

	public:
		void Resize(const System::Size2D<T>&  ac_NewDimensions);
		void RePosition(const System::Point2D<T>& ac_ScreenPos);
		void ReBind(const System::Point2D<T>& ac_NewRelativePos);

		void Update();

		const System::Point2D<T>& GetScreenPos();
		const System::Point2D<T>  GetWorldPos();
		const System::Size2D<T>&  GetDimensions();
		const System::Size2D<T>&  GetResolution();
		const System::Size2D<T>&  GetZoom();
		const T GetRotation();
		const unsigned int GetWindowIndex();
		const unsigned int GetWorldSpace();

		Camera(
			const System::Point2D<T>&	 ac_ScreenPos,
			const System::Point2D<T>&	 ac_WorldPos,
			const System::Point2D<T>&	 ac_RelativePos,
			const System::Size2D<T>&	 ac_Dimension,
			const System::Size2D<T>&	 ac_Resolution,
			const System::Size2D<T>&	 ac_Zoom,
			const T						 ac_Rotation,
			const bool					 ac_bIsScrolling,
			const System::AngularVel<T>& ac_Velocity,
			const unsigned int			 ac_uiWindowIndex,
			const unsigned int			 ac_uiWorldSpace);
		Camera() = delete;
		~Camera();
	};

	struct CameraUnion // Allows for int || float 'Camera' objects to be stored in the same vector
	{
		enum { INT, FLOAT }Tag; // Since it is an unnamed struct, 'Tag' becomes a member variable of type enum
		union
		{
			Camera<int>*   iCamera; // The int type of 'Camera'
			Camera<float>* fCamera; // The float type of 'Camera'
		};
	};
	extern std::vector<CameraUnion*> voCameras; // The vector that holds each type of 'Camera' object

	// - Makes sure when the window is resized that all 'Camera' objects resize to match it
	template <typename T>
	void ResizeCameras(Camera<T>& a_Camera, const System::Size2D<unsigned int>& ac_uiDimensions, const unsigned int ac_uiIndex);

	// - Creates a 'new Camera' object and passes it the following parameters
	template <typename T = int>
	void NewCamera(
		const System::Point2D<T>&	   ac_ScreenPos = { 0, 0 },			// Where the 'Camera' object should be placed relative to the screen
		const System::Point2D<T>&	   ac_WorldPos = { 0, 0 },			// Where in the World the 'Camera' object should start in the world. Serves as an offset to 'm_RelativePos'
		const System::Point2D<T>&	   ac_RelativePos = { 0, 0 },		// What point if any the 'Camera' should be anchored to, such as a player object's 'Point2D'
		const System::Size2D<T>&	   ac_Dimensions = { 100, 100 },	// The size of the 'Camera' object relative to the window size
		const System::Size2D<T>&	   ac_Zoom = { 1, 1 },				// The zoom in of the 'Camera' object
		const T						   ac_Rotation = 0,					// The rotation of the 'Camera' object
		const bool					   ac_bIsScrolling = false,			// Whether or not the 'Camera' object scrolls
		const System::AngularVel<T>&   ac_Velocity = { 0, 0 },			// If the 'Camera' object scrolls, it needs a velocity as well
		const unsigned int			   ac_uiWindowIndex = 0,			// Which window the 'Camera' object should affect
		const unsigned int			   ac_uiWorldSpace = 0);			// Which world space the 'Camera' object exists in. This can be any positive number

																		// - Pushes a 'Camera' of type int into the 'voCamera' vector
	void PushCamera(Camera<int>* a_Camera);
	// - Pushes a 'Camera' of type int into the 'voCamera' vector
	void PushCamera(Camera<float>* a_Camera);
}

// All functions that can be called from 'Graphics::' regarding the camera class
namespace Graphics
{
	template <typename T>
	void NewCamera(
		const System::Point2D<T>&	   ac_ScreenPos,
		const System::Point2D<T>&	   ac_WorldPos,
		const System::Point2D<T>&	   ac_RelativePos,
		const System::Size2D<T>&	   ac_Dimensions,
		const System::Size2D<T>&	   ac_Zoom,
		const T						   ac_Rotation,
		const bool					   ac_bIsScrolling,
		const System::AngularVel<T>&   ac_Velocity,
		const unsigned int			   ac_uiWindowIndex,
		const unsigned int			   ac_uiWorldSpace)
	{
		System::Size2D<T> SizeOffset = { ac_Dimensions.W * (T)voWindows[ac_uiWindowIndex]->GetDimensions().W / 100.0f, ac_Dimensions.H * (T)voWindows[ac_uiWindowIndex]->GetDimensions().H / 100.0f };
		System::Point2D<T> ScreenOffset = {
			ac_ScreenPos.X * (T(voWindows[ac_uiWindowIndex]->GetDimensions().W) - SizeOffset.W) / 100.0f,
			abs(ac_ScreenPos.Y - 100.0f) * (T(voWindows[ac_uiWindowIndex]->GetDimensions().H) - SizeOffset.H) / 100.0f };

		System::Size2D<T> Resolution = {
			(T)voWindows[ac_uiWindowIndex]->GetResolution().W * ((float)SizeOffset.W / (float)voWindows[ac_uiWindowIndex]->GetDimensions().W),
			(T)voWindows[ac_uiWindowIndex]->GetResolution().H * ((float)SizeOffset.H / (float)voWindows[ac_uiWindowIndex]->GetDimensions().H) };

		Camera<T>* newCamera = new Camera<T>(ScreenOffset, ac_WorldPos, ac_RelativePos, SizeOffset, Resolution, ac_Zoom, ac_Rotation, ac_bIsScrolling, ac_Velocity, ac_uiWindowIndex, ac_uiWorldSpace);
		PushCamera(newCamera);
	}

	template <typename T>
	void ResizeCameras(Camera<T>& a_Camera, const System::Size2D<unsigned int>& ac_uiDimensions, const unsigned int ac_uiIndex)
	{
		if (a_Camera.GetWindowIndex() == ac_uiIndex)
		{
			System::Size2D<T> Scale = {
				(T)((float)voWindows[a_Camera.GetWindowIndex()]->GetDimensions().W / (float)a_Camera.GetDimensions().W) * 100.0f,
				(T)((float)voWindows[a_Camera.GetWindowIndex()]->GetDimensions().H / (float)a_Camera.GetDimensions().H) * 100.0f };

			System::Size2D<T> SizeOffset = { Scale.W * (T)ac_uiDimensions.W / 100.0f, Scale.H * (T)ac_uiDimensions.H / 100.0f };

			a_Camera.Resize(SizeOffset);
		}
	}
}

namespace Graphics
{
	template <typename T>
	void Camera<T>::Resize(const System::Size2D<T>& ac_NewDimensions)
	{
		m_Dimensions = ac_NewDimensions;
	}
	template <typename T>
	void Camera<T>::RePosition(const System::Point2D<T>& ac_NewScreenPos)
	{
		m_ScreenPos = ac_NewScreenPos;
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
			m_WorldPos += m_Velocity;
	}

	template <typename T>
	const System::Point2D<T>& Camera<T>::GetScreenPos()
	{
		return m_ScreenPos;
	}
	template <typename T>
	const System::Point2D<T> Camera<T>::GetWorldPos()
	{
		return m_WorldPos + *m_RelativePos;
	}
	template <typename T>
	const System::Size2D<T>& Camera<T>::GetDimensions()
	{
		return m_Dimensions;
	}
	template <typename T>
	const System::Size2D<T>& Camera<T>::GetResolution()
	{
		return m_Resolution;
	}
	template <typename T>
	const System::Size2D<T>& Camera<T>::GetZoom()
	{
		return m_Zoom;
	}
	template <typename T>
	const T Camera<T>::GetRotation()
	{
		return m_Rotation;
	}
	template <typename T>
	const unsigned int Camera<T>::GetWindowIndex()
	{
		return m_uiWindowIndex;
	}
	template <typename T>
	const unsigned int Camera<T>::GetWorldSpace()
	{
		return m_uiWorldSpace;
	}

	template <typename T>
	Camera<T>::Camera(
		const System::Point2D<T>&	 ac_ScreenPos,
		const System::Point2D<T>&	 ac_WorldPos,
		const System::Point2D<T>&	 ac_RelativePos,
		const System::Size2D<T>&	 ac_Dimension,
		const System::Size2D<T>&	 ac_Resolution,
		const System::Size2D<T>&	 ac_Zoom,
		const T						 ac_Rotation,
		const bool					 ac_bIsScrolling,
		const System::AngularVel<T>& ac_Velocity,
		const unsigned int			 ac_uiWindowIndex,
		const unsigned int			 ac_uiWorldSpace)
	{
		m_ScreenPos =	 ac_ScreenPos;
		m_WorldPos =	 ac_WorldPos;
		m_RelativePos = &ac_RelativePos;

		m_Dimensions = ac_Dimension;
		m_Resolution = ac_Resolution;

		m_Zoom =	 ac_Zoom;
		m_Rotation = ac_Rotation;

		m_bIsScrolling = ac_bIsScrolling;

		m_Velocity = ac_Velocity;

		m_uiWindowIndex = ac_uiWindowIndex;
		m_uiWorldSpace =  ac_uiWorldSpace;
	}
	template <typename T>
	Camera<T>::~Camera()
	{

	}
}

#endif // _CAMERA_H_
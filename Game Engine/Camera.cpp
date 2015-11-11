#include "Camera.h"

namespace Graphics
{
	void PushCamera(Camera<int>* a_Camera)
	{
		CameraUnion* newCameraUnion = new CameraUnion;

		newCameraUnion->Tag = CameraUnion::INT;
		newCameraUnion->iCamera = a_Camera;

		voCameras.push_back(newCameraUnion);
	}
	void PushCamera(Camera<float>* a_Camera)
	{
		CameraUnion* newCameraUnion = new CameraUnion;

		newCameraUnion->Tag = CameraUnion::FLOAT;
		newCameraUnion->fCamera = a_Camera;

		voCameras.push_back(newCameraUnion);
	}
}
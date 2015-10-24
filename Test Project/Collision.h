#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Graphics.h"

namespace Collision
{
	class Object;

	struct BoundingBox
	{
		System::Point2D<float> Min, Max;
		System::Point2D<float> Center;

		bool bIsTrigger;
		bool bCheckOthers; // Whether to check this bounding boxes against all other bounding boxes

		Object* oObject;
	};

	void Init();

	void Collisions();

	void FindHost(const BoundingBox& a_oObject, const unsigned int ac_uiIndex);
	void CheckCollisions(const BoundingBox& a_oHost, BoundingBox& a_oOther);

	BoundingBox* NewBoundingBox(const Object* ac_oObject, const bool ac_bIsTrigger, const bool ac_bCheckOthers);

	void Quit();
}

namespace Collision
{
	BoundingBox* NewBoundingBox(Object* ac_oObject, const bool ac_bIsTrigger, const bool ac_bCheckOthers)
	{
		BoundingBox* bbBoundingBox = new BoundingBox;

		bbBoundingBox->Min = { NULL, NULL };
		bbBoundingBox->Max = { NULL, NULL };

		bbBoundingBox->Center = { NULL, NULL };

		bbBoundingBox->bIsTrigger = ac_bIsTrigger;
		bbBoundingBox->bIsTrigger = ac_bCheckOthers;

		bbBoundingBox->oObject = ac_oObject;

		voBoundingBoxes.push_back(bbBoundingBox);

		return bbBoundingBox;
	}
}
#endif // _COLLISION_H_


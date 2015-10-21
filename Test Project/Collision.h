#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Graphics.h"

#define CALL_MEMBER_FN(OBJ, FUNC) ((OBJ).*(FUNC)) // Makes calling function pointers using an object much less clunky

namespace Collision
{
	template <typename T>
	class Object;

	template <typename T>
	struct BoundingBox
	{
		System::Point2D<T> Min, Max;
		System::Size2D<T> Size;

		bool bIsTrigger;
		bool bCheckOthers; // Whether to check this bounding boxes against all other bounding boxes

		Object<T>* oObject;
		void(Object<T>::*CallBack)(void) CallBackFunc;
	};

	struct BoundingBoxUnion
	{
		enum { INT, FLOAT } Tag;
		union
		{
			BoundingBox<int>*   iBoundingBox;
			BoundingBox<float>* fBoundingBox;
		};
	};

	void Init();

	void Collisions();

	template <typename T>
	void FindHost(const BoundingBox<T>& a_oObject, const unsigned int ac_uiIndex);
	template <typename T, typename U>
	void CheckCollisions(const BoundingBox<T>& a_oHost, BoundingBox<U>& a_oOther);

	template <typename T>
	BoundingBox<T>* NewBoundingBox(const Object<T>* ac_oObject, const System::Size2D<T>& ac_Size, const bool ac_bIsTrigger, const bool ac_bCheckOthers);

	void PushBoundingBox(BoundingBox<int>*	 a_bbBoundingBox);
	void PushBoundingBox(BoundingBox<float>* a_bbBoundingBox);

	void Quit();
}

namespace Collision
{
	template <typename T>
	BoundingBox<T>* NewBoundingBox(Object<T>* ac_oObject, const System::Size2D<T>& ac_Size, const bool ac_bIsTrigger, const bool ac_bCheckOthers)
	{
		BoundingBox<T>* bbBoundingBox = new BoundingBox<T>;

		bbBoundingBox->oObject = ac_oObject;

		bbBoundingBox->Size = ac_Size;

		bbBoundingBox->bIsTrigger = ac_bIsTrigger;
		bbBoundingBox->bIsTrigger = ac_bCheckOthers;

		bbBoundingBox->Min = { NULL, NULL };
		bbBoundingBox->Max = { NULL, NULL };

		PushBoundingBox(bbBoundingBox);

		return bbBoundingBox;
	}
}
#endif // _COLLISION_H_

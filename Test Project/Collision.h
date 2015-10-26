#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Graphics.h"

namespace Collision
{
	struct BoundingBox;

	class Object
	{
	protected:

		System::Point2D<float> m_fPos;
		System::Point2D<int>   m_iPos;

		System::Velocity2D<float> m_fVelocity;
		System::AngularVel<float> m_fAngularVel;

		bool m_bMove;

		
	public:
		BoundingBox* m_bbBoundingBox;

		void Handle();
		void LateHandle();

		virtual void Update();
		virtual void LateUpdate();

		void Move();

		virtual void OnCollision(Object& a_oOther);

		virtual void UpdateBB();

		const System::Point2D<float>& GetPos();
		const System::Point2D<int>& GetIntPos();

		const BoundingBox& GetBoundingBox();

		Object();
		~Object();
	};
}
namespace Collision
{
	struct BoundingBox
	{
		System::Point2D<float> fMin, fMax;
		System::Point2D<float> fCenter;

		System::Size2D<float> fSize;

		bool bIsTrigger;
		bool bCheckOthers; // Whether to check this bounding boxes against all other bounding boxes

		Object* oObject;
	};

	void Init();

	void CheckCollisions();

	BoundingBox* NewBoundingBox(Object* ac_oObject, const System::Size2D<float>& ac_fSize, const System::Point2D<float>& ac_fPos, const bool ac_bIsTrigger, const bool ac_bCheckOthers);

	void Quit();
}
#endif // _COLLISION_H_


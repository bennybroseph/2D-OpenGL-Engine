#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Graphics.h"
#include "GameTime.h"

namespace Collision
{
	struct BoundingBox;
	struct BoundingCircle;

	class Object
	{
	protected:
		System::Point2D<float> m_fPos, m_fPrevPos;
		System::Point2D<int>   m_iPos;

			

		System::Velocity2D<float> m_fVelocity;
		System::AngularVel<float> m_fAngularVel;

		float m_fMass;

		bool m_bMove, m_bUseGravity;
		
	public:
		BoundingBox* m_bbBoundingBox;

		void Handle();
		void LateHandle();

		virtual void Update();
		virtual void LateUpdate();

		void Move();

		void OnCollision(Object& a_oOther);
		virtual void OnBoxCollision(Object& a_oOther);
		virtual void OnMovingCollision(Object& a_oOther);

		virtual void UpdateBB();

		const System::Point2D<float>& GetPos();
		const System::Point2D<int>& GetIntPos();

		const System::Velocity2D<float>& GetVel();

		const BoundingBox& GetBB();

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
		
		bool bActive;

		Object* oObject;
	};

	void Init();

	void CheckCollisions();
	void CheckBB();

	BoundingBox* NewBoundingBox(Object* a_oObject, const System::Point2D<float>& ac_fPos, const System::Size2D<float>& ac_fSize, const bool ac_bIsTrigger, const bool ac_bCheckOthers);

	void Quit();
}
#endif // _COLLISION_H_


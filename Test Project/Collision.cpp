#include "Collision.h"



namespace Collision
{
	std::vector<BoundingBoxUnion*> voBoundingBoxes;

	void Init()
	{

	}

	void Collisions()
	{
		for (int i = 0; i < voBoundingBoxes.size(); ++i)
		{
			switch (voBoundingBoxes[i]->Tag)
			{
			case BoundingBoxUnion::INT: FindHost(*voBoundingBoxes[i]->iBoundingBox, i); break;
			case BoundingBoxUnion::FLOAT: FindHost(*voBoundingBoxes[i]->fBoundingBox, i);  break;
			}
		}
	}

	template <typename T>
	void FindHost(const BoundingBox<T>& a_oObject, const unsigned int ac_uiIndex)
	{
		if (a_oObject.bCheckOthers)
		{
			for (int i = 0; i < voBoundingBoxes.size(); ++i)
			{
				if (i != ac_uiIndex)
				{
					switch (voBoundingBoxes[i]->Tag)
					{
					case BoundingBoxUnion::INT: CheckCollisions(a_oObject, *voBoundingBoxes[i]->iBoundingBox); break;
					case BoundingBoxUnion::FLOAT: CheckCollisions(a_oObject, *voBoundingBoxes[i]->fBoundingBox);  break;
					}
				}
			}
		}
	}
	template <typename T, typename U>
	void CheckCollisions(const BoundingBox<T>& a_oHost, BoundingBox<U>& a_oOther)
	{
		if (a_oHost.Max.X < a_oOther.Min.X) return;
		if (a_oHost.Max.X < a_oOther.Min.X) return;
		if (a_oHost.Max.X < a_oOther.Min.X) return;
		if (a_oHost.Max.X < a_oOther.Min.X) return;

		a_oHost.oObject->OnCollision();
	}

	void PushBoundingBox(BoundingBox<int>* a_bbBoundingBox)
	{
		BoundingBoxUnion* newBoundingBox = new BoundingBoxUnion;

		newBoundingBox->Tag = BoundingBoxUnion::INT;
		newBoundingBox->iBoundingBox = a_bbBoundingBox;

		voBoundingBoxes.push_back(newBoundingBox);
	}
	void PushBoundingBox(BoundingBox<float>* a_bbBoundingBox)
	{
		BoundingBoxUnion* newBoundingBox = new BoundingBoxUnion;

		newBoundingBox->Tag = BoundingBoxUnion::FLOAT;
		newBoundingBox->fBoundingBox = a_bbBoundingBox;

		voBoundingBoxes.push_back(newBoundingBox);
	}

	void Quit()
	{

	}
}

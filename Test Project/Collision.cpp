#include "Collision.h"



namespace Collision
{
	std::vector<BoundingBox*> voBoundingBoxes;

	void Init()
	{

	}

	void CheckCollisions()
	{
		for (int i = 0; i < voBoundingBoxes.size(); ++i)
		{
			for (int j = 0; j < voBoundingBoxes.size(); ++j)
			{
				if (i != j)
				{
					float fD1X = voBoundingBoxes[i]->fMin.X - voBoundingBoxes[j]->fMax.X;
					float fD1Y = voBoundingBoxes[i]->fMin.Y - voBoundingBoxes[j]->fMax.Y;

					float fD2X = voBoundingBoxes[j]->fMin.X - voBoundingBoxes[i]->fMax.X;
					float fD2Y = voBoundingBoxes[j]->fMin.Y - voBoundingBoxes[i]->fMax.Y;

					if (fD1X > 0.0f || fD1Y > 0.0f)
						return;
					if (fD2X > 0.0f || fD2Y > 0.0f)
						return;

					voBoundingBoxes[i]->oObject->OnCollision(*voBoundingBoxes[j]->oObject);
				}
			}
		}
	}

	BoundingBox* NewBoundingBox(Object* ac_oObject, const System::Size2D<float>& ac_fSize, const System::Point2D<float>& ac_fPos, const bool ac_bIsTrigger, const bool ac_bCheckOthers)
	{
		BoundingBox* bbBoundingBox = new BoundingBox;

		bbBoundingBox->fMin = { NULL, NULL };
		bbBoundingBox->fMax = { NULL, NULL };

		bbBoundingBox->fCenter = ac_fPos;

		bbBoundingBox->fSize = ac_fSize;

		bbBoundingBox->bIsTrigger = ac_bIsTrigger;
		bbBoundingBox->bIsTrigger = ac_bCheckOthers;

		bbBoundingBox->oObject = ac_oObject;

		voBoundingBoxes.push_back(bbBoundingBox);

		return bbBoundingBox;
	}

	void Quit()
	{

	}
}

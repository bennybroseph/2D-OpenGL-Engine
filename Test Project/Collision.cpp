#include "Collision.h"



namespace Collision
{
	std::vector<BoundingBox*> voBoundingBoxes;
	std::vector<BoundingCircle*> voBoundingCircles;

	void Init()
	{

	}

	void CheckCollisions()
	{
		CheckBB();
		CheckBC();
	}
	void CheckBB()
	{
		for (int i = 0; i < voBoundingBoxes.size(); ++i)
		{
			if (voBoundingBoxes[i]->bCheckOthers && voBoundingBoxes[i]->bActive)
			{
				for (int j = 0; j < voBoundingBoxes.size(); ++j)
				{
					if (i != j)
					{
						float fD1X = voBoundingBoxes[i]->fMin.X - voBoundingBoxes[j]->fMax.X;
						float fD1Y = voBoundingBoxes[i]->fMin.Y - voBoundingBoxes[j]->fMax.Y;

						float fD2X = voBoundingBoxes[j]->fMin.X - voBoundingBoxes[i]->fMax.X;
						float fD2Y = voBoundingBoxes[j]->fMin.Y - voBoundingBoxes[i]->fMax.Y;

						if (fD1X >= 0.0f || fD1Y >= 0.0f)
							return;
						if (fD2X >= 0.0f || fD2Y >= 0.0f)
							return;

						voBoundingBoxes[i]->oObject->OnCollision(*voBoundingBoxes[j]->oObject);
					}
				}
				/*for (int j = 0; j < voBoundingCircles.size(); ++j)
				{
					float fD1X = voBoundingBoxes[i]->fMin.X - (voBoundingCircles[j]->fCenter.X + voBoundingCircles[j]->fRadius);
					float fD1Y = voBoundingBoxes[i]->fMin.Y - (voBoundingCircles[j]->fCenter.Y + voBoundingCircles[j]->fRadius);

					float fD2X = (voBoundingCircles[j]->fCenter.X - voBoundingCircles[j]->fRadius) - voBoundingBoxes[i]->fMax.X;
					float fD2Y = (voBoundingCircles[j]->fCenter.Y - voBoundingCircles[j]->fRadius) - voBoundingBoxes[i]->fMax.Y;

					if (fD1X >= 0.0f || fD1Y >= 0.0f)
						return;
					if (fD2X >= 0.0f || fD2Y >= 0.0f)
						return;

					voBoundingBoxes[i]->oObject->OnCollision(*voBoundingCircles[j]->oObject);
				}*/
			}
		}
	}
	void CheckBC()
	{

	}

	BoundingBox* NewBoundingBox(Object* a_oObject, const System::Point2D<float>& ac_fPos, const System::Size2D<float>& ac_fSize, const bool ac_bIsTrigger, const bool ac_bCheckOthers)
	{
		BoundingBox* bbBoundingBox = new BoundingBox;

		bbBoundingBox->fMin = { NULL, NULL };
		bbBoundingBox->fMax = { NULL, NULL };

		bbBoundingBox->fCenter = ac_fPos;

		bbBoundingBox->fSize = ac_fSize;

		bbBoundingBox->bIsTrigger = ac_bIsTrigger;
		bbBoundingBox->bIsTrigger = ac_bCheckOthers;

		bbBoundingBox->oObject = a_oObject;

		voBoundingBoxes.push_back(bbBoundingBox);

		return bbBoundingBox;
	}
	BoundingCircle* NewBoundingCircle(Object* a_oObject, const System::Point2D<float>& ac_fCenter, const float ac_fRadius, const bool ac_bIsTrigger, const bool ac_bCheckOthers)
	{
		BoundingCircle* bcBoundingCircle = new BoundingCircle;

		bcBoundingCircle->fCenter = ac_fCenter;

		bcBoundingCircle->fRadius = ac_fRadius;

		bcBoundingCircle->bIsTrigger = ac_bIsTrigger;
		bcBoundingCircle->bCheckOthers = ac_bCheckOthers;

		bcBoundingCircle->oObject = a_oObject;

		voBoundingCircles.push_back(bcBoundingCircle);

		return bcBoundingCircle;
	}

	void Quit()
	{

	}
}

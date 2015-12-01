////////////////////////////////////////////////////////////
// File: LoopHandle.cpp
// Author: Ben Odom
// Date Created: 10/01/2015
////////////////////////////////////////////////////////////

#include "LoopHandle.h"

#include <ctime>

const unsigned int ONE_SECOND = 1000;

namespace LoopHandle
{
	void Init()
	{
		HWND consoleWindow = GetConsoleWindow(); // Get the current console window
		SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER); // Move it to the Top Left and don't change its size or 'z' order

		Graphics::Init();
		Text::Init("Fonts/Pokemon Red.ttf", { 255, 255, 255, 255 }, 32);
		Time::Init();

		Graphics::NewWindow({ 1600, 900 }, false, { 1600, 900 }, "New Window", 1);

		/*srand(time(NULL));

		float fCurrentTime = 0;
		float fPreviousTime = 0;
		float fDeltaTime = 0;

		float fAnimateTime = 0;

		System::Point2D<float> Center = { 800, 400 };

		System::Point2D<float> CirclePos = { 0, 0 };

		System::Point2D<float> LineBeginPos = { Center.X, Center.Y + 250 }, LineEndPos = { Center.X, Center.Y + 350 };

		System::Color<float> CircleColor = { 255, 255, 255, 255 };

		float fMovementRadius = 50;
		float fAngle = 0, fLineAngle = 0;

		bool bFade = true;
		bool bAnimateLine = false;

		bool bMoveLeft = true;
		bool bZoom = false;

		Graphics::GLSurface<float>* Eyes = Graphics::LoadSurface<float>("Images/Eyes.png");
		Graphics::GLSurface<float>* NewEyes = Graphics::LoadSurface<float>("Images/Eyes.png");

		float fZoomTime = 0, fNewZoomTime = 0;
		float fZoomSpeed = 0.1, fNewZoomSpeed = 0.1;

		NewEyes->Pos = Center;
		NewEyes->bIsActive = false;
		NewEyes->Scale = { 0.001f, 0.001f };
		NewEyes->Center = { 180, 80 };

		Eyes->Pos = { 314 / 2, 219 / 2 };
		Eyes->Center = { 180, 80 };

		bool bEyesHigh = false;

		while (true)
		{
			if (GetAsyncKeyState(VK_SPACE))
				bAnimateLine = true;
			if (GetAsyncKeyState(VK_RETURN))
			{
				Eyes->Scale = { 0.001f, 0.001f };
				bZoom = true;
			}

			fPreviousTime = fCurrentTime;
			fCurrentTime = clock();
			fDeltaTime = (fCurrentTime - fPreviousTime) / ONE_SECOND;

			fAngle += 5 * fDeltaTime;
			CirclePos = { fMovementRadius * cosf(fAngle), fMovementRadius * sinf(fAngle) };
			CirclePos += Center;

			if (bFade)
				CircleColor.Alpha -= 100 * fDeltaTime;
			else
				CircleColor.Alpha += 100 * fDeltaTime;

			if (bFade && CircleColor.Alpha <= 0)
			{
				CircleColor.Alpha = 0;
				bFade = false;
			}
			else if (!bFade && CircleColor.Alpha >= 255)
			{
				CircleColor.Alpha = 255;
				bFade = true;
			}

			if (bAnimateLine)
			{
				fAnimateTime += fDeltaTime;

				if (bMoveLeft)
					fLineAngle += 2 * fDeltaTime;
				else
					fLineAngle -= 2 * fDeltaTime;

				if (bMoveLeft && fLineAngle >= PI)
				{
					fLineAngle = PI;
					bMoveLeft = false;
				}
				else if (!bMoveLeft && fLineAngle <= 0)
				{
					fLineAngle = 0;
					bMoveLeft = true;
				}

				LineBeginPos = { 100 * cosf(fLineAngle), -100 * sinf(fLineAngle) + 350 };
				LineBeginPos += Center;

				if (fAnimateTime > 5)
				{
					fAnimateTime = 0;
					fLineAngle = 0;
					bAnimateLine = false;
				}
			}

			CircleColor.Blue = rand() % 255;
			CircleColor.Green = rand() % 255;
			CircleColor.Red = rand() % 255;

			if (bZoom)
			{
				if (Eyes->bIsActive)
				{
					Eyes->Pos = Center;
					Eyes->Scale.W += fZoomSpeed * fDeltaTime;
					Eyes->Scale.H = Eyes->Scale.W;

					fZoomSpeed += fZoomSpeed * 1.7 * fDeltaTime;
					fZoomTime += fDeltaTime;

					if (fZoomTime >= 3)
					{
						bEyesHigh = true;
						NewEyes->bIsActive = true;
					}
					if (fZoomTime >= 6)
					{
						bEyesHigh = false;
						fZoomTime = 0;
						Eyes->Scale = { 0.01f, 0.01f };
						fZoomSpeed = 0.1;
					}
				}

				if (NewEyes->bIsActive)
				{
					NewEyes->Scale.W += fNewZoomSpeed * fDeltaTime;
					NewEyes->Scale.H = NewEyes->Scale.W;

					fNewZoomSpeed += fNewZoomSpeed * 1.7 * fDeltaTime;
					fNewZoomTime += fDeltaTime;

					if (fNewZoomTime >= 3)
					{
						bEyesHigh = false;
					}
					if (fNewZoomTime >= 6)
					{
						bEyesHigh = true;
						fNewZoomTime = 0;
						NewEyes->Scale = { 0.01f, 0.01f };
						fNewZoomSpeed = 0.1;
					}
				}
			}

			Graphics::DrawCircle(CirclePos, 100.0f, 50.0f, CircleColor);
			Graphics::DrawLine(LineBeginPos, LineEndPos, { 255, 0, 255, 255 });
			Graphics::DrawLine({ 0, 0 }, CirclePos, CircleColor);
			Graphics::DrawLine({ 0, 900 }, CirclePos, CircleColor);
			Graphics::DrawLine({ 1600, 0 }, CirclePos, CircleColor);
			Graphics::DrawLine({ 1600, 900 }, CirclePos, CircleColor);
			if (bEyesHigh)
			{
				Graphics::DrawSurface(*Eyes);
				Graphics::DrawSurface(*NewEyes);
			}
			else
			{
				Graphics::DrawSurface(*NewEyes);
				Graphics::DrawSurface(*Eyes);
			}

			Graphics::Flip();
		}*/

		srand((unsigned int)time(NULL));

		GameLoop oGameLoop;

		oGameLoop.Run();
	}

	void Handle()
	{

	}

	void Quit()
	{
		Graphics::Quit();
	}
}


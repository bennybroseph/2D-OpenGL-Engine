////////////////////////////////////////////////////////////
// File: Text.cpp
// Author: Ben Odom
// Date Created: 10/01/2015
////////////////////////////////////////////////////////////

#include "Text.h"

namespace Text
{
	std::vector<FontData*> voFontData;

	bool Init(const char* ac_szFilename, const System::Color<int>& ac_iColor, const int ac_iSize)
	{
		if (TTF_Init() == 1)
		{
			printf("TTF_Init: %s\n", TTF_GetError());
			return 1;
		}

		if (LoadFont(ac_szFilename, ac_iColor, ac_iSize) == nullptr)
			return 1;

		return 0;
	}

	void Print(const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText)
	{
		Print(*voFontData[0], ac_iPos, ac_bAlign, ac_szText);
	}
	void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText)
	{
		std::vector<std::string> vsLines;

		char szHold[256];
		strcpy_s(szHold, "");

		const char* i;
		if ((i = strchr(ac_szText, 10)) != NULL)
		{
			strncat_s(szHold, ac_szText, int(i - ac_szText));
			vsLines.push_back(szHold);

			strcpy_s(szHold, i + 1);
			vsLines.push_back(szHold);
		}
		else
		{
			vsLines.push_back(ac_szText);
		}

		std::vector<SDL_Surface*> vsdlTemp;
		Graphics::GLSurface<int>* glSurface;

		int width = 0, height = 0;
		// Write text to surface
		for (int j = 0; j < vsLines.size(); ++j)
		{
			vsdlTemp.push_back(TTF_RenderUTF8_Blended(ac_ttfFont.ttfFont, vsLines[j].c_str(), { (Uint8)ac_ttfFont.iColor.Red, (Uint8)ac_ttfFont.iColor.Blue, (Uint8)ac_ttfFont.iColor.Green, (Uint8)ac_ttfFont.iColor.Alpha }));

			if (vsdlTemp[j]->w > width)
				width = vsdlTemp[j]->w;

			height += vsdlTemp[j]->h;
		}

		SDL_Surface* sdlSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
		SDL_Rect TextPos;

		for (int j = 0; j < vsdlTemp.size(); ++j)
		{
			TextPos = { 0, j*(height / (int)vsdlTemp.size()), width, height };
			SDL_BlitSurface(vsdlTemp[j], NULL, sdlSurface, &TextPos);
		}
		glSurface = Graphics::LoadSurface<int>(*sdlSurface);
		glSurface->Pos = { ac_iPos.X + (ac_bAlign)*(glSurface->Dimensions.W / 2), ac_iPos.Y + (ac_bAlign)*(glSurface->Dimensions.H / 2) };
		glSurface->Layer = Graphics::LayerType::OVERLAY;

		//Graphics::DeleteSurface(glSurface);
	}

	void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const int ac_iText)
	{
		char szBuffer[256];

		sprintf_s(szBuffer, "%d", ac_iText);
		Print(ac_ttfFont, ac_iPos, ac_bAlign, szBuffer);
	}

	FontData* LoadFont(const char* ac_szFilename, const System::Color<int>& ac_iColor, const int ac_iSize)
	{
		FontData* NewFont = new FontData;

		NewFont->ttfFont = TTF_OpenFont(ac_szFilename, ac_iSize);

		NewFont->iColor = ac_iColor;

		NewFont->iSize = ac_iSize;

		if (NewFont->ttfFont == NULL)
		{
			printf("Failure to load \"%s\"\n", ac_szFilename);
			return nullptr;
		}

		for (int i = 0; i < 256; i++)
		{
			if (TTF_GlyphMetrics(NewFont->ttfFont, i,
				&NewFont->aoChar[i].iMin.X, &NewFont->aoChar[i].iMax.X, &NewFont->aoChar[i].iMin.Y, &NewFont->aoChar[i].iMax.Y,
				&NewFont->aoChar[i].iAdvance) == -1)
			{
				printf("%s\n", TTF_GetError());
				return nullptr;
			}
		}

		voFontData.push_back(NewFont);

		return NewFont;
	}

	void Quit()
	{
		for (int i = 0; i < voFontData.size(); ++i)
			TTF_CloseFont(voFontData[i]->ttfFont);

		TTF_Quit();
	}
}

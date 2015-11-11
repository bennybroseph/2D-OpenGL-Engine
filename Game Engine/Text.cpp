////////////////////////////////////////////////////////////
// File: Text.cpp
// Author: Ben Odom
// Date Created: 11/02/2015
////////////////////////////////////////////////////////////

#include "Text.h"

namespace Text
{
	std::vector<FontData*> voFontData;
	std::vector<TextBlockUnion*> voTextBlocks;

	bool Init(const char* ac_szFilename, const System::Color<int>& ac_iColor, const unsigned int ac_uiSize)
	{
		if (TTF_Init() == 1)
		{
			printf("TTF_Init: %s\n", TTF_GetError());
			return 1;
		}

		if (LoadFont(ac_szFilename, ac_iColor, ac_uiSize) == nullptr)
			return 1;

		return 0;
	}

	void Print(const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText)
	{
		//Print(*voFontData[0], ac_iPos, ac_bAlign, ac_szText);
	}
	void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText)
	{
		
	}

	void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const int ac_iText)
	{
		char szBuffer[256];

		sprintf_s(szBuffer, "%d", ac_iText);
		Print(ac_ttfFont, ac_iPos, ac_bAlign, szBuffer);
	}

	FontData* LoadFont(const char* ac_szFilename, const System::Color<int>& ac_iColor, const unsigned int ac_uiSize)
	{
		FontData* newFont = new FontData;

		newFont->ttfFont = TTF_OpenFont(ac_szFilename, ac_uiSize);

		newFont->iColor = ac_iColor;

		newFont->iSize = ac_uiSize;

		if (newFont->ttfFont == NULL)
		{
			printf("Failure to load \"%s\"\n", ac_szFilename);
			return nullptr;
		}

		for (int i = 0; i < 256; i++)
		{
			if (TTF_GlyphMetrics(newFont->ttfFont, i,
				&newFont->aoChar[i].iMin.X, &newFont->aoChar[i].iMax.X, &newFont->aoChar[i].iMin.Y, &newFont->aoChar[i].iMax.Y,
				&newFont->aoChar[i].iAdvance) == -1)
			{
				printf("%s\n", TTF_GetError());
				return nullptr;
			}
		}

		voFontData.push_back(newFont);

		return newFont;
	}

	void Quit()
	{
		for (unsigned int i = 0; i < voFontData.size(); ++i)
			TTF_CloseFont(voFontData[i]->ttfFont);

		TTF_Quit();
	}
}

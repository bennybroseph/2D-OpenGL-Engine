/////////////////////////////////////////////////////////////
// File: Text.h
// Author: Ben Odom
// Brief: Holds functionality for drawing text to the screen
//        using SDL_TTF. Can draw text string and integers.
//////////////////////////////////////////////////////////////

#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL_ttf.h>

#include "Graphics.h"

namespace Text
{
    struct FontData
    {
        TTF_Font* ttfFont;

        System::Color<int> iColor;

		int iSize;

		struct Glyph
		{
			System::Point2D<int> iMin, iMax;
			int iAdvance;
		};

		Glyph aoChar[256];
    };

    bool Init(const char* ac_szFilename, const System::Color<int>& ac_iColor, const int ac_iSize);
    
	void Print(const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText);
	void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText);
    void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const int ac_iText);

	FontData* LoadFont(const char* ac_szFilename, const System::Color<int>& ac_iColor, const int ac_iSize);

	void Quit();
}

#endif  //_TEXT_H_

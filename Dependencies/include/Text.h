/////////////////////////////////////////////////////////////
// File: Text.h
// Author: Ben Odom
// Brief: Holds functionality for drawing text to the screen
//        using SDL_TTF. Can draw text string and integers.
//////////////////////////////////////////////////////////////

#ifndef _TEXT_H_
#define _TEXT_H_

#include "Graphics.h"

#include <SDL_ttf.h>

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
	extern std::vector<FontData*> voFontData;

	template <typename T>
	struct TextBlock
	{
		char* szText;

		Graphics::GLSurface<T>* glSurface;

		FontData* ttfFontData;
	};
	struct TextBlockUnion
	{
		enum { INT, FLOAT }Tag;
		union
		{
			TextBlock<int>*	  iGLSurface;
			TextBlock<float>* fGLSurface;
		};
	};
	extern std::vector<TextBlockUnion*> voTextBlocks;

	// Defines the default font type, as one must exist to do anything else
	bool Init(const char* ac_szFilename, const System::Color<int>& ac_iColor, const int ac_iSize);

	void Print(const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const char* ac_szText);
	
	template <typename T = int>
	TextBlock<T>* LoadTextBlock(const System::Point2D<T>& ac_iPos, const bool ac_bAlign, char* ac_szText);
	template <typename T = int>
	TextBlock<T>* LoadTextBlock(FontData* ac_ttfFont, const System::Point2D<T>& ac_iPos, const bool ac_bAlign, char* ac_szText);
	template <typename T = int>
	void ReloadTextBlock(TextBlock<T>* a_ttfTextBlock, const bool ac_bAlign, char* ac_szText);

	void Print(const FontData &ac_ttfFont, const System::Point2D<int>& ac_iPos, const bool ac_bAlign, const int ac_iText);

	FontData* LoadFont(const char* ac_szFilename, const System::Color<int>& ac_iColor, const int ac_iSize);

	void Quit();
}

namespace Text
{
	template <typename T>
	TextBlock<T>* LoadTextBlock(const System::Point2D<T>& ac_iPos, const bool ac_bAlign, char* ac_szText)
	{
		return LoadTextBlock(voFontData[0], ac_iPos, ac_bAlign, ac_szText);
	}
	template <typename T>
	TextBlock<T>* LoadTextBlock(FontData* ac_ttfFont, const System::Point2D<T>& ac_iPos, const bool ac_bAlign, char* ac_szText)
	{
		TextBlock<T>* newTextBlock = new TextBlock<T>;

		newTextBlock->ttfFontData = ac_ttfFont;
		newTextBlock->glSurface = nullptr;

		ReloadTextBlock(newTextBlock, ac_bAlign, ac_szText);

		newTextBlock->glSurface->Pos = { ac_iPos.X + (ac_bAlign)*(newTextBlock->glSurface->Dimensions.W / 2), ac_iPos.Y };
		newTextBlock->glSurface->Layer = Graphics::LayerType::OVERLAY;

		return newTextBlock;
	}
	template <typename T>
	void ReloadTextBlock(TextBlock<T>* a_ttfTextBlock, const bool ac_bAlign, char* ac_szText)
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

		int width = 0, height = 0;
		// Write text to surface
		for (int j = 0; j < vsLines.size(); ++j)
		{
			vsdlTemp.push_back(TTF_RenderUTF8_Blended(
				a_ttfTextBlock->ttfFontData->ttfFont, 
				vsLines[j].c_str(), 
				{ (Uint8)a_ttfTextBlock->ttfFontData->iColor.Red, (Uint8)a_ttfTextBlock->ttfFontData->iColor.Blue, (Uint8)a_ttfTextBlock->ttfFontData->iColor.Green, (Uint8)a_ttfTextBlock->ttfFontData->iColor.Alpha }));

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

			SDL_FreeSurface(vsdlTemp[j]);
		}

		a_ttfTextBlock->szText = ac_szText;

		if (a_ttfTextBlock->glSurface == nullptr)
			a_ttfTextBlock->glSurface = Graphics::LoadSurface<T>(*sdlSurface);
		else
		{
			Graphics::ReloadSurface(a_ttfTextBlock->glSurface, *sdlSurface);

			a_ttfTextBlock->glSurface->Dimensions = { sdlSurface->w, sdlSurface->h };
			a_ttfTextBlock->glSurface->OffsetD = { sdlSurface->w, sdlSurface->h };

			a_ttfTextBlock->glSurface->Center.X = a_ttfTextBlock->glSurface->Dimensions.W / 2.0f;
			a_ttfTextBlock->glSurface->Center.Y = a_ttfTextBlock->glSurface->Dimensions.H / 2.0f;
		}

		
	}
}

#endif  //_TEXT_H_

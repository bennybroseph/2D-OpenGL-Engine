////////////////////////////////////////////////////////////
// File: Text.cpp
// Author: Ben Odom
// Date Created: 11/02/2015
// Brief: Holds functionality for drawing text to the screen
//        using SDL_TTF. Can draw text string and integers.
////////////////////////////////////////////////////////////

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

		System::Point2D<T> PosOffset;

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
	bool Init(const char* ac_szFilename, const System::Color<int>& ac_iColor, const unsigned int ac_uiSize);

	template <typename T = int>
	TextBlock<T>* LoadTextBlock(const System::Point2D<T>& ac_iPos, const bool ac_bAlign, char* ac_szText);
	template <typename T = int>
	TextBlock<T>* LoadTextBlock(FontData* ac_ttfFont, const System::Point2D<T>& ac_iPos, const bool ac_bAlign, char* ac_szText);
	template <typename T = int>
	void ReloadTextBlock(TextBlock<T>* a_ttfTextBlock, const bool ac_bAlign, char* ac_szText);

	template <typename T = int>
	void DeleteTextBlock(TextBlock<T>* a_ttfTextBlock);

	FontData* LoadFont(const char* ac_szFilename, const System::Color<int>& ac_iColor, const unsigned int ac_uiSize);

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

		newTextBlock->PosOffset = { (ac_bAlign)*(newTextBlock->glSurface->Size.W / 2), 0 };

		newTextBlock->glSurface->Pos = ac_iPos;
		newTextBlock->glSurface->Pos += newTextBlock->PosOffset;

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
		for (unsigned int j = 0; j < vsLines.size(); ++j)
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

		for (unsigned int j = 0; j < vsdlTemp.size(); ++j)
		{
			TextPos = { 0, (int)j*(height / (int)vsdlTemp.size()), width, height };
			SDL_BlitSurface(vsdlTemp[j], NULL, sdlSurface, &TextPos);

			SDL_FreeSurface(vsdlTemp[j]);
		}

		a_ttfTextBlock->szText = ac_szText;

		if (a_ttfTextBlock->glSurface == nullptr)
			a_ttfTextBlock->glSurface = Graphics::LoadSurface<T>(*sdlSurface);
		else
		{
			Graphics::ReloadSurface(a_ttfTextBlock->glSurface, *sdlSurface);
			SDL_FreeSurface(sdlSurface);

			a_ttfTextBlock->glSurface->Size = { sdlSurface->w, sdlSurface->h };
			a_ttfTextBlock->glSurface->OffsetSize = { sdlSurface->w, sdlSurface->h };

			a_ttfTextBlock->glSurface->Center.X = a_ttfTextBlock->glSurface->Size.W / (T)2.0f;
			a_ttfTextBlock->glSurface->Center.Y = a_ttfTextBlock->glSurface->Size.H / (T)2.0f;
		}
		a_ttfTextBlock->glSurface->Pos -= a_ttfTextBlock->PosOffset;
		a_ttfTextBlock->PosOffset = { (ac_bAlign)*(a_ttfTextBlock->glSurface->Size.W / 2), 0 };
		a_ttfTextBlock->glSurface->Pos += a_ttfTextBlock->PosOffset;
	}
}

#endif  //_TEXT_H_

#pragma once
#include "SDL2_ttf/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf/lib/x86/SDL2_ttf.lib")
#include<string>
#include<iostream>


class Text
{
private:

	SDL_Texture* fontTexture(TTF_Font* font, std::string text);
public:

};


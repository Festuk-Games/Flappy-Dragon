#pragma once

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )
#include "TextureManager.h"
#include <iostream>

class Object
{

private: 
	SDL_Rect src, dest;
	SDL_Texture* Tex;

public:
	Object();
	void setSource(int x, int y, int w, int h);
	void setDest(int x, int y, int w, int h);
	SDL_Texture* getTexture();
	SDL_Rect& getSrc();
	SDL_Rect& getDest();
	void CreateTexture(const char* adress, SDL_Renderer* ren);
	void virtual Render(SDL_Renderer* ren) = 0;
};

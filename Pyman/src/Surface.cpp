/* 
 * File:   Surface.cpp
 * Author: frosty
 * 
 * Created on January 16, 2014, 2:00 PM
 */

#include "Surface.h"

Surface::Surface()
{
    surface = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);
}

Surface::Surface(SDL_Surface* s)
{
    surface = s;
}

Surface::Surface(int w, int h, int bpp)
{
    surface = SDL_CreateRGBSurface(0, w, h, bpp, 0, 0, 0, 0);
}

SDL_Surface* Surface::getSurface() const
{
    return surface;
}

void Surface::setSurface(SDL_Surface* s)
{
	if (surface != NULL)
		SDL_FreeSurface(surface);
	surface = s;
}

void Surface::applySurface(int x, int y, Surface* s)
{
        SDL_Rect offset;
        offset.x = x;
        offset.y = y;

        SDL_BlitSurface(s->getSurface(), NULL, surface, &offset);
}

void Surface::applySurface(SDL_Rect* loc, Surface* s)
{
	SDL_BlitSurface(s->getSurface(),NULL,surface,loc);
}

void Surface::applySurface(int x, int y, SDL_Surface* src, const SDL_Rect* clip)
{
	SDL_Rect offset;
    offset.x = x;
	offset.y = y;

	SDL_BlitSurface(src, clip, surface, &offset);
}

Surface::~Surface()
{
    SDL_FreeSurface(surface);
}

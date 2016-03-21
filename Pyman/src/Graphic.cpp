/* 
 * File:   Graphic.cpp
 * Author: frosty
 * 
 * Created on March 3, 2014, 3:32 PM
 */

#include "Graphic.h"

Graphic::Graphic() {
}

Graphic::Graphic(SDL_Surface* s)
{
	surface = new Surface(s);
}

const map<string, SDL_Rect>* Graphic::getClips() const
{
	return clips;
}

void Graphic::addClip(const string& type, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	clips->insert(pair<string,SDL_Rect>(type,rect));
}

void Graphic::draw()
{
	Display::surface->applySurface(position, surface);
}

Graphic::~Graphic() {
	delete position, surface, clips;
}


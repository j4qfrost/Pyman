/*
 * Button.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: frosty
 */

#include "Button.h"

Button::Button()
{
	bounds = NULL;
	source = NULL;
	flag = NULL;
	count = 0;
	capacity = 4;
	state = 0;
	clips = new SDL_Rect[capacity];
}

Button::Button(SDL_Rect* grab, bool& f, const string& file)
{
    bounds = grab;

	capacity = 4;
	count = 0;

	clips = new SDL_Rect[capacity];

    SDL_Surface* loaded = SDL_LoadBMP(file.c_str());
    if (loaded != NULL)
    {
    	source = SDL_ConvertSurfaceFormat(loaded, surface->getSurface()->format->format,
    										surface->getSurface()->flags);
    	SDL_FreeSurface(loaded);
    }

    addClip(0,0,bounds->w,bounds->h);

    flag = &f;
}

SDL_Surface* Button::getSource() const
{
	return source;
}

void Button::setSource(const string& file)
{
    SDL_Surface* loaded = NULL;
	string ext = file.substr(file.size() - 4);
	if (ext == ".bmp")
		loaded = SDL_LoadBMP(file.c_str());
	else if (ext == ".png")
		loaded = IMG_Load(file.c_str());
	else
		printf("Unsupported format!\n");

    if (loaded != NULL)
    {
        source = SDL_ConvertSurfaceFormat(loaded, surface->getSurface()->format->format,
        									surface->getSurface()->flags);
		SDL_FreeSurface(loaded);
    }
}

void Button::setCoordinates(int x, int y)
{
    bounds->x = x;
    bounds->y = y;
}

void Button::setBounds(int w, int h)
{
    bounds->w = w;
    bounds->h = h;

    addClip(0,0,w,h);
    addClip(w,0,w,h);
}

void Button::setFlag(bool& f)
{
    flag = &f;
}

void Button::setParams(int x, int y, int w, int h, bool& f, const string& file)
{
	if (bounds == NULL)
		bounds = new SDL_Rect;

    setCoordinates(x,y);
    setBounds(w,h);
    setFlag(f);
    setSource(file);
}



void Button::addClip(int x, int y, int w, int h)
{
    clips[count].x = x;
    clips[count].y = y;
    clips[count].w = w;
    clips[count].h = h;

    count++;
}


void Button::handle()
{
    int x = 0;
    int y = 0;

    if (e.type == SDL_MOUSEMOTION)
    {
        x = e.motion.x;
        y = e.motion.y;

        if ((x > bounds->x) && (x < bounds->x + bounds->w) &&
                (y > bounds->y) && (y < bounds->y + bounds->h) &&
                count > 1)
            state = 1;
        else
            state = 0;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
		{
            x = e.button.x;
            y = e.button.y;


            if ((x > bounds->x) && (x < bounds->x + bounds->w) &&
                (y > bounds->y) && (y < bounds->y + bounds->h))
            {
				if (count > 2)
					state = 2;
                *flag = !(*flag);
            }
		}
    }
}

void Button::show()
{
	if (clips == NULL)
		SDL_FillRect(surface->getSurface(),bounds,1000);
	else
		surface->applySurface(bounds->x,bounds->y,source,&clips[state]);
}

Button::~Button()
{
    delete [] clips;
	delete flag;
    clips = NULL;
	flag = NULL;
	SDL_FreeSurface(source);
}

/*
 * File:   main.cpp
 * Author: frosty
 *
 * Created on January 13, 2014, 1:37 PM
 */

#include "Character.h"
#include "setup.h"

#include "Selector.h"

#include <iostream>

using namespace std;

bool Manage::ingame = true;
bool Manage::editing = false;
bool Manage::scriptReload = false;
SDL_Event Manage::e;
Surface* Display::surface = NULL;

Selector* selector = NULL;

#include "Console.h"
#include "Tracker.h"

/*
 *
 */

Uint32 WALL = 0;

bool collision(unsigned dir, SDL_Rect* box)
{
	SDL_Rect surfaceRect = surface->getSurface()->clip_rect;
	unsigned eval = 0;
	switch (dir)
	{
	case 0:
		eval = (box->y + box->h)*surfaceRect.w + box->x;
		break;
	case 1:
		eval = (box->y + box->h)*surfaceRect.w + box->x;
		break;
	case 2:
		eval = (box->y + box->h)*surfaceRect.w + box->x;
		break;
	case 3:
		eval = (box->y + box->h)*surfaceRect.w + box->x;
		break;
	default:
		return false;
		break;
	}
	Uint32 pixel = ((Uint32*)surface->getSurface()->pixels)[eval];
	return pixel == WALL;
}

void gravity(SDL_Rect* box, bool grounded)
{
	if (!grounded)
		box->y += 2;
}

bool onGround(SDL_Rect* box)
{
	return collision(3, box);
}

void drawBlocks(const Package* const package)
{
	for(unsigned int i = 0; i < package->count; i++)
	{
		if (package->objects[i]->getHackFlag())
		{
			package->objects[i]->update();
			SDL_FillRect(surface->getSurface(), package->objects[i]->getPos(), SDL_MapRGB(surface->getSurface()->format, 0, 255, 0));
		}
		else
			SDL_FillRect(surface->getSurface(), package->objects[i]->getPos(), WALL);
	}
}

void changeLanguage(string language)
{
	for (auto l : Manage::VALID_LANG)
	{
		if (l == language)
		{
			Manage::lang = language;
			break;
		}
	}
}

int main(int argc, char** argv)
{
	SDL_Surface* background = IMG_Load("res/test_red.png");

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

    if (mainframeInit() < 0)
        exit(-1);

	SDL_MapRGB(surface->getSurface()->format, 255, 0, 0);
	SDL_Surface* bgOptimized = SDL_ConvertSurface(background,surface->getSurface()->format,NULL);
	/*  optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
	if( optimizedSurface == NULL )
	{
	printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface ); */

	SDL_FreeSurface(background);

    Uint32 ticks;
    bool running = true;
    Uint32 backColor = SDL_MapRGB(surface->getSurface()->format,255,255,255);
    SDL_FillRect(surface->getSurface(),&surface->getSurface()->clip_rect,
    				backColor);

    SDL_Rect* gBound = new SDL_Rect;
    gBound->x = 0;
    gBound->y = surface->getSurface()->clip_rect.h - 10;
    gBound->w = surface->getSurface()->clip_rect.w;
    gBound->h = 10;

    Console* console = new Console;
    Button* consoleButton = new Button;
    consoleButton->setParams(0,0,20,20,Manage::editing,"res/closeButton.png");

    SDL_Rect* charCoord = new SDL_Rect();
    charCoord->x = 50;
    charCoord->y = 50;
    charCoord->w = 10;
    charCoord->h = 10;
    int velX = 0;
    int velY = 0;
    int airTime = 0;

    selector = new Selector("levels/test1.xml");
    Package* package = selector->sendPackage();

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    while(running)
    {
   		velX = 0, velY = 0;
   		if (airTime > 0)
   		{
   			velY = -4;
   			airTime--;
   		}
        ticks = SDL_GetTicks();

        if (SDL_PollEvent(&Manage::e))
        {
        	if (Manage::e.type == SDL_QUIT)
        	{
        		running = false;
        	}
        	else if (Manage::ingame)
        	{
        		if (Manage::editing)
        		{
        			console->handleEvent();
					if (Manage::scriptReload)
					{
						delete package;
						package = selector->sendPackage();
						Manage::scriptReload = false;
					}
        		}
        	}
        }
        else if (console->inBounds() && Manage::editing)
        	console->idling();

        if (!Manage::editing)
        {
			SDL_FillRect(surface->getSurface(), &(surface->getSurface()->clip_rect),backColor);
        	//drawBlocks(package);
			surface->applySurface(0,0,bgOptimized,NULL);

			consoleButton->handle();
			consoleButton->show();

			SDL_FillRect(surface->getSurface(),charCoord,0);

			if (keyboardState[SDL_SCANCODE_W] && onGround(charCoord))
				airTime = 15;
			if (keyboardState[SDL_SCANCODE_S] && !onGround(charCoord))
				velY += 2;
			if (keyboardState[SDL_SCANCODE_D])
				velX += 2;
			if (keyboardState[SDL_SCANCODE_A])
				velX -= 2;

			gravity(charCoord,onGround(charCoord));

			charCoord->x += velX;
			charCoord->y += velY;
        }

        if (ticks % 1000 > 600 && console->inBounds() && Manage::editing)
        {
        	SDL_FillRect(Display::surface->getSurface(),console->getAbsCursorPos(),1000);
        }

        redraw();
        stopWatch(ticks);
    }
    cleanup();

    return 0;
}



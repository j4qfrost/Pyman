/*
 * helpers.h
 *
 *  Created on: Mar 19, 2014
 *      Author: frosty
 */

#ifndef AUXILARY_H_
#define AUXILARY_H_

#include "externs.h"

SDL_Window* Display::window = NULL;
SDL_Renderer* Display::renderer = NULL;
SDL_Texture* Display::texture = NULL;

int mainframeInit()
{
	if (!SDL_WasInit(SDL_INIT_EVERYTHING) && !SDL_Init(SDL_INIT_EVERYTHING) < 0)
	        return -1;

    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_BORDERLESS,
                                        &Display::window, &Display::renderer);
    if (!(Display::window && Display::renderer))
        return -1;

    Display::texture = SDL_CreateTexture(Display::renderer, SDL_PIXELFORMAT_ARGB8888,
                                        SDL_TEXTUREACCESS_STREAMING, 640, 480);
    if (!Display::texture)
        return -1;

    SDL_SetRenderDrawColor(Display::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Display::renderer);
    SDL_RenderPresent(Display::renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Display::renderer, 640, 480);

    Display::surface = new Surface(SDL_GetWindowSurface(Display::window));

    return 0;
}

void stopWatch(int t)
{
	Uint32 current = SDL_GetTicks();
	if(current - t < 1000 / Manage::FPS)
	{
		SDL_Delay(1000 / Manage::FPS - (current - t));
	}
}

void redraw()
{
	SDL_UpdateTexture(Display::texture, NULL, Display::surface->getSurface()->pixels,
						Display::surface->getSurface()->pitch);
	SDL_RenderClear(Display::renderer);
	SDL_RenderCopy(Display::renderer, Display::texture, NULL, NULL);
	SDL_RenderPresent(Display::renderer);
}

void cleanup()
{
    SDL_DestroyTexture(Display::texture);
    SDL_DestroyWindow(Display::window);
    SDL_DestroyRenderer(Display::renderer);
    SDL_Quit();
}


#endif /* AUXILARY_H_ */

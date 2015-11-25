/* 
 * File:   Surface.h
 * Author: frosty
 *
 * Created on January 16, 2014, 2:00 PM
 * Abstract:	This class extends the SDL_Surface struct
 *				with additional functionality specific to
 *				the working environment of the game.
 */

#ifndef SURFACE_H_
#define	SURFACE_H_

#include <SDL.h>

class Surface {
public:
    Surface();
    
    Surface(SDL_Surface* s);

    Surface(int w, int h, int bpp);

    SDL_Surface* getSurface() const;

    void setSurface(SDL_Surface* s);

    void applySurface(int x, int y, Surface* s);
    void applySurface(SDL_Rect* loc, Surface* s);
    void applySurface(int x, int y, SDL_Surface* src, const SDL_Rect* clip);
    
    virtual ~Surface();
private:
    SDL_Surface* surface;
};

#endif	/* SURFACE_H_ */


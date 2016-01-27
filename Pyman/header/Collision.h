/*
* File:   Surface.h
* Author: frosty
*
* Created on January 16, 2014, 2:00 PM
* Abstract:	This class extends the SDL_Surface struct
*				with additional functionality specific to
*				the working environment of the game.
*/

#ifndef COLLISION_H_
#define	COLLISION_H_

#include <SDL.h>
#include "externs.h"

using Display::surface;

class Collision {
public:
	Collision() {}

	bool collides(unsigned dir, const SDL_Rect* box) const;
	void gravity(SDL_Rect* box, bool grounded);

	const Uint32 WALL = 16711680;
};

#endif	/* COLLISION_H_ */


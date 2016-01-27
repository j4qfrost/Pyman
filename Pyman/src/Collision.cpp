#include "Collision.h"

bool Collision::collides(unsigned dir, const SDL_Rect* box) const
{
	SDL_Rect surfaceRect = surface->getSurface()->clip_rect;
	unsigned eval = 0;
	switch (dir)
	{
	case 0: //left
		eval = (box->y)*surfaceRect.w + box->x - 1;
		break;
	case 1: //up
		eval = (box->y)*surfaceRect.w + box->x + box->w / 2;
		break;
	case 2: //right
		eval = (box->y)*surfaceRect.w + box->x + box->w;
		break;
	case 3: //down
		eval = (box->y + box->h)*surfaceRect.w + box->x + box->w / 2;
		break;
	default:
		return false;
		break;
	}
	Uint32 pixel = ((Uint32*)surface->getSurface()->pixels)[eval];
	return pixel == WALL;
}

void Collision::gravity(SDL_Rect* box, bool grounded)
{
	if (!grounded)
		box->y += 2;
}
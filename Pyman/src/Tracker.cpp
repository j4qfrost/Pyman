/*
 * Tracker.cpp
 *
 *  Created on: Mar 17, 2014
 *      Author: frosty
 */

#include "Tracker.h"

Tracker::Tracker()
{
}

void Tracker::handle() {
	if (e.button.button == SDL_BUTTON_LEFT)
		std::cout << "(" << e.button.x << "," << e.button.y << ")\n";
}

Tracker::~Tracker()
{
}


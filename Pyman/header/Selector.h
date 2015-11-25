/*
 * Selector.h
 *
 * Created on: Apr 29, 2014
 * Author: frosty
 * Abstract:	This class generates packages for the game
 *				environment to generate objects. Currently
 *				only Python is supported.
 */

#ifndef SELECTOR_H_
#define SELECTOR_H_

#include "pugixml.hpp"

#include <SDL.h>
#include "Platform.h"

class Package
{
public:
	Package();
	~Package();

	BaseObject** objects;
	int count;
	void destroyObjects();
};

class Selector {
public:
	Selector();
	Selector(const char* fileName);

	void generateLevel(const char* fileName);
	void regenerateLevel(const char* fileName);

	Package* sendPackage() const;

	virtual ~Selector();

private:
	SDL_Rect* blocks;
	Uint32* colors;
	unsigned int index;
};

#endif /* SELECTOR_H_ */

/*
 * externs.h
 *
 *  Created on: Mar 19, 2014
 *      Author: frosty
 */

#ifndef EXTERNS_H_
#define EXTERNS_H_

#include "Surface.h"
#include <string>
using std::string;

namespace Display {
	extern SDL_Window* window;
	extern SDL_Renderer* renderer;
	extern SDL_Texture* texture;
	extern Surface* surface;
}

namespace Manage {
	const unsigned int FPS = 60;
	extern SDL_Event e;
	extern bool ingame;
	extern bool editing;
	extern bool scriptReload;
	const int LANG_COUNT = 2;
	const string VALID_LANG[LANG_COUNT] = {
		"python",
		"cplusplus"
	};

	static string lang = "python";
}

#endif /* EXTERNS_H_ */

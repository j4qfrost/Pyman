/*
 * File:   BaseObject.h
 * Author: frosty
 *
 * Published on November 25, 2015, 12:13 AM
 * Abstract:	This class is the base object for all interactable
 *				objects in the game. It currently has Python support
 *				and will be extended appropriately.
 */

#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include "Surface.h"
#include <string>
using std::string;
#include "PyInterface.h"

class BaseObject {
public:
	BaseObject();
	virtual ~BaseObject();
	void setPos(SDL_Rect* rect);
	void setPos(int x, int y, int w, int h);

	bool getHackFlag() const;
	string getType() const;
	string getID() const;
	SDL_Rect* getPos() const;

	void setCallable(PyObject* pointer);
	virtual void update();

protected:
	bool hackable;
	string id;
	string type;
	SDL_Rect* pos;

	PyObject* callable;
};

#endif
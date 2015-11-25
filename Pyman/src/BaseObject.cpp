#include "BaseObject.h"

BaseObject::BaseObject()
{
	type = "base";
	id = "no-id";
	hackable = false;
	callable = NULL;
	pos = new SDL_Rect;
}

void BaseObject::setPos(SDL_Rect* rect)
{
	pos->x = rect->x;
	pos->y = rect->y;
	pos->w = rect->w;
	pos->h = rect->h;
}

void BaseObject::setPos(int x, int y, int w, int h)
{
	pos->x = x;
	pos->y = y;
	pos->w = w;
	pos->h = h;
}

bool BaseObject::getHackFlag() const
{
	return hackable;
}

string BaseObject::getType() const
{
	return type;
}

string BaseObject::getID() const
{
	return id;
}

SDL_Rect* BaseObject::getPos() const
{
	return pos;
}

void BaseObject::setCallable(PyObject* pointer)
{
	hackable = true;
	callable = pointer;
}

void BaseObject::update()
{
	printf("This is the base.");
}

BaseObject::~BaseObject()
{
	delete pos;
	pos = NULL;

	Py_CLEAR(callable);
}
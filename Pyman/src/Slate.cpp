/*
 * Slate.cpp
 *
 *  Created on: Mar 17, 2014
 *      Author: frosty
 */

#include "Slate.h"

Slate::Slate()
{
	clickX = 0;
	clickY = 0;
	offset = NULL;

	block = 0;
}

Slate::Slate(const char* newScript) : FileText(newScript)
{
	clickX = 0;
	clickY = 0;
	offset = NULL;

	block = 10;
}

Slate::Slate(const char* newScript, unsigned int fontSize) : FileText(newScript)
{
	clickX = 0;
	clickY = 0;
	offset = NULL;

	block = fontSize;
}

void Slate::handle()
{
	if ((e.button.x > offset->x && e.button.y > offset->y) &&
		(e.button.x < offset->x + offset->w && e.button.y < offset->y + offset->h))
	{
		clickX = e.button.x - offset->x;
		clickY = e.button.y - offset->y;
	}
	clickToCursor();
}

void Slate::insert(const char* c)
{
	clickToCursor();
	FileText::insert(c,cursor);
	returnCursor();
}

int Slate::back()
{
	clickToCursor();
	int merged = FileText::back(cursor);
	returnCursor();
	return merged;
}

void Slate::newLine()
{
	FileText::newLine(cursor);
	returnCursor();
}

void Slate::setCanvas(SDL_Rect* can)
{
	offset = can;
}

void Slate::clickToCursor()
{
	cursor.pos = clickX / (block - 4);
	cursor.li = clickY / block;
}

void Slate::resetCoord()
{
	clickX = cursor.pos * (block - 4);
	clickY = cursor.li * block;
}

void Slate::returnCursor()
{
	FileText::returnCursor(cursor);
	resetCoord();
}

void Slate::shiftToLineStart()
{
	cursor.pos = 0;
	returnCursor();
}

void Slate::shiftToEnd()
{
	cursor.li = getLines().size() - 1;
	cursor.pos = getLines()[cursor.li].size();

	resetCoord();
}

const Cursor& Slate::getCursor() const
{
	return cursor;
}

void Slate::shiftCursor(unsigned int dir)
{
	switch(dir) {
	case 0:
		cursor.pos--;
		break;
	case 1:
		cursor.pos++;
		break;
	case 2:
		cursor.li--;
		break;
	case 3:
		cursor.li++;
	}
	returnCursor();
}

Slate::~Slate()
{
	delete offset;
	offset = NULL;
}


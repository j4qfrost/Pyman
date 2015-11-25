/*
 * Menu.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: frosty
 */

#include "Menu.h"

Menu::Menu(int boxX, int boxY, int boxW, int boxH)
{
    capacity = 10;

	offset = new SDL_Rect;

    offset->x = boxX;
    offset->y = boxY;
    offset->w = 0;
    offset->h = 0;

    w = boxW;
    h = boxH;

    buttonList = new Button [capacity];
    count = 0;
}

Button* Menu::getButton(int i) const
{
	return (buttonList + i);
}

SDL_Rect* Menu::getOffset() const
{
	return offset;
}

void Menu::addButton(const string& file, bool& flag)
{
    (buttonList + count)->setParams(offset->x,offset->y,w,h,flag,file);

	offset->y += h;
    count++;
}

void Menu::showMenu()
{
    for(unsigned int i = 0; i < count; i++)
    {
        (buttonList + i)->show();
    }
}

void Menu::handleMenu()
{
    for(unsigned int i = 0; i < count; i++)
    {
        (buttonList + i)->handle();
    }
}

Menu::~Menu()
{
    delete offset;
    delete [] buttonList;
    offset = NULL;
    buttonList = NULL;
}

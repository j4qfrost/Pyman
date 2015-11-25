/*
 * Menu.h
 *
 * Created on: Mar 23, 2014
 * Author: frosty
 * Abstract:	This class manages GUI options, namely
 *				buttons. This is a carry over from
 *				BattleSnake.
 */

#ifndef MENU_H_
#define MENU_H_

#include "Button.h"

class Menu {
public:
    Menu(int boxX, int boxY, int boxW, int boxH);

    virtual ~Menu();

	Button* getButton(int i) const;
	SDL_Rect* getOffset() const;

    void addButton(const string& file, bool& flag);
    void showMenu();
    void handleMenu();

private:
    Button* buttonList;
    SDL_Rect* offset;
    int w;
    int h;
    unsigned int count;
    unsigned int capacity;
};

#endif /* MENU_H_ */

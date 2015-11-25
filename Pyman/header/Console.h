/* 
 * File:   Console.h
 * Author: frosty
 *
 * Created on February 28, 2014, 2:18 AM
 * Abstract:	This class integrates components together
 *				in order to create a scripting environment.
 *				Actual console output is a future extension.
 */

#ifndef CONSOLE_H_
#define	CONSOLE_H_

#include "PyInterface.h"
#include "Slate.h"
#include "Button.h"
#include <SDL_ttf.h>

class Console {
public:
    Console();

    void handleEvent();
    SDL_Rect* getAbsCursorPos() const;

    void setFont(const char* newFont);

    void renderLines();
    void renderLine(unsigned int i);

    void draw();
    void redraw(int multiple);
    void idling();
    bool inBounds() const;
    
    const char* getFontName() const;
    
    virtual ~Console();

private:
    Slate* slate;

    TTF_Font* font;
    string fontName;
    unsigned int fontSize;

    SDL_Color color;
    Surface* frame;
    SDL_Rect* sandBox;
    SDL_Rect* textBox;
    SDL_Rect* errBox;

    Button* closeButton;
};

#endif	/* CONSOLE_H_ */


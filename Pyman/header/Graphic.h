/* 
 * File:   Graphic.h
 * Author: frosty
 *
 * Created on March 3, 2014, 3:32 PM
 * Abstract:	This class handles graphical assets.
 */

#ifndef GRAPHIC_H_
#define	GRAPHIC_H_

#include <map>

#include "Sprite.h"
#include "externs.h"

class Graphic : public Sprite {
public:
    Graphic();
    Graphic(SDL_Surface* s);
    
    const map<string,SDL_Rect>* getClips() const;
    
    void addClip(const string& type, int x, int y, int w, int h);
	virtual void draw();

	SDL_Rect* position;
    
    virtual ~Graphic();
private:
    map<string,SDL_Rect>* clips;
    Surface* surface;
};

#endif	/* GRAPHIC_H_ */

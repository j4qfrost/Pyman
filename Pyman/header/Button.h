/*
 * Button.h
 *
 * Created on: Mar 23, 2014
 * Author: frosty
 * Abstract:	This class is a customizable GUI element
 *				supported by a Tracking class and an image
 *				loader.
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Tracker.h"
#include <string>
#include <SDL_image.h>

using std::string;
using Display::surface;

class Button : public Tracker {
public:
	Button();

    Button(SDL_Rect* grab, bool& f, const string& file);

    virtual ~Button();

	SDL_Surface* getSource() const;

    void setSource(const string& file);
    void setCoordinates(int x, int y);
    void setBounds(int w, int h);
    void setFlag(bool& f);
    void setParams(int x, int y, int w, int h, bool& f, const string& file);

	void addClip(int x, int y, int w, int h);

    virtual void handle();
    void show();


private:
	SDL_Rect* clips;
    SDL_Rect* bounds;
    bool* flag;
	SDL_Surface* source;
    unsigned int count;
    unsigned int capacity;
    unsigned int state;
};

#endif /* BUTTON_H_ */

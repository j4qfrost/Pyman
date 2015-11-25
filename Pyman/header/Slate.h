/*
 * Slate.h
 *
 * Created on: Mar 17, 2014
 * Author: frosty
 * Abstract:	This class is a text editor... yep.
 */

#ifndef SLATE_H_
#define SLATE_H_

#include "Tracker.h"
#include "FileText.h"

class Slate : public Tracker, public FileText {
public:
	unsigned int block;

	Slate();
	Slate(const char* newScript);
	Slate(const char* newScript, unsigned int fontSize);

	void handle();
	void setCanvas(SDL_Rect* can);

	void insert(const char* c);
	int back();
	void newLine();

	void clickToCursor();
	void resetCoord();
	void returnCursor();
	void shiftToLineStart();
	void shiftToEnd();

	const Cursor& getCursor() const;
	void shiftCursor(unsigned int dir);

	virtual ~Slate();
private:
	int clickX;
	int clickY;
	Cursor cursor;
	SDL_Rect* offset;
};

#endif /* SLATE_H_ */

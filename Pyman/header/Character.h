/* 
 * File:   Character.h
 * Author: frosty
 *
 * Created on January 18, 2014, 7:18 PM
 * Abstract:	For ease of prototyping, this currently
 *				functions as the player. This class will
 *				be converted to a base character class for
 *				modularity.
 */

#ifndef CHARACTER_H_
#define	CHARACTER_H_

#include "Graphic.h"

class Character : public Graphic {
public:
    Character();
    Character(const Character& orig);
    
    virtual ~Character();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void draw();

	const string name;

private:
	map<string, void*>* actionMap;
	map<string, string>* dialogue;

	//NOTE: ideas of menu pause arose from texteditor
};

#endif	/* CHARACTER_H_ */


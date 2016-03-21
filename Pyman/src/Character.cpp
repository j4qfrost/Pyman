/* 
 * File:   Character.cpp
 * Author: frosty
 * 
 * Created on January 18, 2014, 7:18 PM
 */

#include "Character.h"

Character::Character() {
}

Character::Character(const Character& orig) {
}

void Character::draw()
{
	Graphic::draw();
}

Character::~Character() {
	
	for (map<string, void*>::iterator it = actionMap->begin(); it != actionMap->end(); it++)
	{
		delete it->second;
		actionMap->erase(it);
	}

	delete actionMap, dialogue;

}


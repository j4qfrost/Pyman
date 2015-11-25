/* 
 * File:   Sprite.h
 * Author: frosty
 *
 * Created on January 19, 2014, 8:41 PM
 * Abstract:	This class is a generic loader for
 *				assets.
 */

#ifndef SPRITE_H_
#define	SPRITE_H_

#include <string>

using namespace std;

class Sprite {
public:
    Sprite();
    Sprite(const Sprite& orig);
    Sprite(void* src);
    
    virtual void* getSource() const;
    
    virtual void setSource(const void* src);
    
    virtual ~Sprite();
private:
    void* source;
};

#endif	/* SPRITE_H_ */


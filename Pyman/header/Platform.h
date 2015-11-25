/*
 * Platform.h
 *
 * Published on: November 25, 2015 1:03 AM
 * Author: frosty
 * Abstract:	See BaseObject.h
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "BaseObject.h"
#include "externs.h"

class Platform : public BaseObject
{
public:
	Platform();
	Platform(const string& ID);
	~Platform();

	virtual void update();

};

#endif
/*
 * Tracker.h
 *
 * Created on: Mar 17, 2014
 * Author: frosty
 * Abstract:	This class tracks mouse movement that
 *				are passed as coordinates from external
 *				variables.
 */

#ifndef TRACKER_H_
#define TRACKER_H_

#include <iostream>
#include "externs.h"

using Manage::e;

class Tracker {
public:
	Tracker();
	virtual ~Tracker();

	virtual void handle();
};

#endif /* TRACKER_H_ */

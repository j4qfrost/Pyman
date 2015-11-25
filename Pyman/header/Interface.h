/*
 * Interface.h
 *
 * Created on: Apr 27, 2014
 * Author: frosty
 *
 * Abstract:	This class is the base interface for interacting
 *				with scripted code. It requires children to have
 *				execution capabilities.
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

class Interface {
public:
	Interface();

	virtual int run(const char* runnable);

	virtual ~Interface();
};

#endif /* INTERFACE_H_ */

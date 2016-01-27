/* 
 * File:   PyInterface.h
 * Author: frosty
 *
 * Created on January 14, 2014, 11:15 AM
 * Abstract:	This class inherits from the base Interface
 *				class. It facilitates interaction between
 *				C++ components and Python components of the
 *				game.
 */

#ifndef PYINTERFACE_H_
#define	PYINTERFACE_H_

#include "Interface.h"
#undef _DEBUG
#include <Python.h>
#include <string>

using std::string;

class PyInterface : public Interface {
public:
	static PyInterface* Instance();
    static int run(const char* runnable);
	
	PyObject* getAttrFromLevel(const char* pName);
	PyObject* getModule(const char* pName);
	PyObject* getAttr(PyObject* from, const char* pName);
	PyObject* functionCallback(const char* pName, int argc, PyObject** argv);

	int setLevel(const char* nlevel);
	int generateLevelObject();
    int addTool(const char* import);
    const char** getTools() const;

	int reload(const char* module);
    int pause();
    int terminate();
    int fetchError() const;
    
    int toggleHint();
    
	int decrefArray(PyObject** pArr, int pCount);
    virtual ~PyInterface();

private:
	PyInterface(const char* nlevel);
	static PyInterface* pi_instance;
	char* packageName;
	char* level;
	PyObject* levelObj;
    PyObject** tools;
	int toolCount;
	const unsigned MAX_TOOL_COUNT = 5;
};

#endif	/* PyInterface_H_ */


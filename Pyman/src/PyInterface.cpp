/* 
 * File:   PyInterface.cpp
 * Author: frosty
 * 
 * Created on January 14, 2014, 11:15 AM
 */

#include "PyInterface.h"

PyInterface* PyInterface::pi_instance = NULL;

PyInterface* PyInterface::Instance()
{
	if (!pi_instance)
		pi_instance = new PyInterface("scripts.__init__");
	return pi_instance;
}

PyInterface::PyInterface(const char* nlevel)
{
    Py_Initialize();

	packageName = "scripts";
	level = new char[50];
	strcpy(level, nlevel);
	generateLevelObject();
	printf("LEVELOBJ: %d\n", levelObj);

	toolCount = 0;
	tools = new PyObject*[MAX_TOOL_COUNT];
    
    PyObject* sys = PyImport_ImportModule("sys");
    PyObject* path = PyObject_GetAttrString(sys,"path");
    
    PyList_Append(path, PyBytes_FromString(""));
    
    Py_DECREF(sys);
}

int PyInterface::run(const char* runnable)
{
	PyRun_SimpleString(runnable);
    return 0;
}


PyObject* PyInterface::getAttrFromLevel(const char* pName)
{
	PyObject* pReturn = PyObject_GetAttrString(levelObj, pName);
	return pReturn;
}

PyObject* PyInterface::getModule(const char* pName)
{
	string temp = string(packageName) + ".";
	return PyImport_ImportModule((temp + pName).c_str());
}

PyObject* PyInterface::getAttr(PyObject* from, const char* pName)
{
	PyObject* pReturn = PyObject_GetAttrString(from, pName);
	Py_DECREF(from);
	return pReturn;
}

PyObject* PyInterface::functionCallback(const char* pName, int argc, PyObject** argv)
{
	PyObject* pFunc = getAttrFromLevel(pName);
	PyObject* pArgs = PyTuple_New(argc);

	printf("pFunc: %d\n",pFunc);

	for (int i = 0; i < argc; i++)
	{
		if (!argv[i])
		{
			PyErr_Print();
			return NULL;
		}
		if(PyTuple_SetItem(pArgs,i,argv[i]))
			exit(-700);
	}

	PyObject* pReturn = PyObject_CallObject(pFunc, pArgs);

	Py_XDECREF(pFunc);
	Py_XDECREF(pArgs);

	return pReturn;
}

int PyInterface::setLevel(const char* nlevel)
{
	if (strcmp(nlevel,level) != 0)
		strcpy(level,nlevel);
	return 0;
}

int PyInterface::generateLevelObject()
{
	levelObj = PyImport_ImportModule(level);
	return 0;
}

int PyInterface::addTool(const char* import)
{
	PyObject* tool = PyImport_ImportModule(import);
	tools[toolCount] = tool;
	toolCount++;

	return 0;
}

int PyInterface::reload(const char* module)
{
	PyObject** argv = new PyObject*[1];
	argv[0] = PyUnicode_FromString(module);
	PyObject* callback = functionCallback("reload",1, argv);

	Py_XDECREF(callback);
	return 0;
}

int PyInterface::pause()
{
	return 0;
}

int PyInterface::terminate()
{
	return 0;
}

int PyInterface::toggleHint()
{
	return 0;
}

int PyInterface::decrefArray(PyObject** pArr, int pCount)
{
	for (int i = 0; i < pCount; i++)
	{
		Py_DECREF(pArr[i]);
	}

	return 0;
}

PyInterface::~PyInterface()
{
	decrefArray(tools, toolCount);
	
	Py_XDECREF(levelObj);
	delete [] level;
	delete [] tools;
	Py_Finalize();
}
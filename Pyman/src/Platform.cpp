#include "Platform.h"

Platform::Platform()
{
	type = "platform";
}

Platform::Platform(const string& ID)
{
	type = "platform";
	id = ID;
}

Platform::~Platform()
{
	if (Manage::lang == "python")
		Py_CLEAR(callable);

	delete pos, callable;
	pos = NULL;
	callable = NULL;
}


void Platform::update()
{
	if (Manage::lang == "python")
	{
		if (PyCallable_Check(callable))
		{
			PyObject* pArgs = PyTuple_New(2);
			PyObject* x = PyLong_FromSize_t(pos->x);
			PyObject* y = PyLong_FromSize_t(pos->y);

			PyTuple_SetItem(pArgs, 0, x);
			PyTuple_SetItem(pArgs, 1, y);

			PyObject* pReturn = PyObject_CallObject(callable, pArgs);

			pos->x = PyLong_AsSize_t(PyTuple_GetItem(pReturn, 0));
			pos->y = PyLong_AsSize_t(PyTuple_GetItem(pReturn, 1));
		}
	}
}
/*
=========================
Building in Visual Studio
=========================

After going through the horrifically agitating process of correctly setting
up the correct properties in Visual Studio, it's time to convert our Cpp
modules to python extensions.

.. note::

	It's important to correctly set the additional include directories and
	additional libs directories.
	This is unintuitive as the default project for the solution is a .pyproj
	which won't display the required properties to set. As a result, one must:

	- Open the solution as standard.
	- Ensure that the Solution Explorer is open and right click the superfastcode project.
	- Either hit :kbd:`Alt+Enter` or Properties.
		- Find ``Additional Includes`` and under the Linker find ``Additional Libs``
		- Ensure that the correct python executable is pointed to. It must be 32 bit.
		- Neither %PYTHONPATH% nor %PYTHONHOME% were set in my case so I hardcoded the paths

Without doing so the entire project and as a result the entire solution won't build which was
admittedly frustrating. Anyways!


Convert the C++ projects to extensions for Python
=================================================
To make the C++ DLL into an extension for Python, you first modify the exported
methods to interact with Python types. You then add a function that exports the
module, along with definitions of the module's methods.

*/

#include <Python.h>
#include <Windows.h>
#include <cmath>

const double e = 2.7182818284590452353602874713527;

double sinh_impl(double x) {
	return (1 - pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double cosh_impl(double x) {
	return (1 + pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double tanh_impl(double x) {
	return sinh_impl(x) / cosh_impl(x);
}

/*
PyObject* tanh_impl(PyObject *, PyObject* o); {
	double x = PyFloat_AsDouble(o);
	double tanh_x = sinh_impl(x) / cosh_impl(x);
	return PyFloat_FromDouble(tanh_x);
}

static PyMethodDef superfastcode_methods[] = {
	// The first property is the name exposed to Python, fast_tanh, the second is the C++
	// function name that contains the implementation.
	{ "fast_tanh", (PyCFunction)tanh_impl, METH_O, nullptr },

	// Terminate the array with an object containing nulls.
{ nullptr, nullptr, 0, nullptr }
};

static PyModuleDef superfastcode_module = {
	PyModuleDef_HEAD_INIT,
	"superfastcode",                        // Module name to use with Python import statements
	"Provides some functions, but faster",  // Module description
	0,
	superfastcode_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_superfastcode() {
	return PyModule_Create(&superfastcode_module);
}

*/
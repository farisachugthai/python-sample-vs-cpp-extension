/*
Removing the bulk of boilerplate with the pybind11 library
==========================================================
So that was an outrageous amount of boilerplate for little implementation.

Update the additional include path that we have established for the second Cpp
project, superfastcode2, so that includes pybind11.

Mine looked like.

`<C:\Program Files (x86)\Microsoft Visual Studio\Shared\Python37_86\lib\site-packages\pybind11\include>`_

This will allow this project to build with substantially less code written.
*/
#include <pybind11/pybind11.h>
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

namespace py = pybind11;

PYBIND11_MODULE(superfastcode2, m) {
	m.def("fast_tanh2", &tanh_impl, R"pbdoc(
        Compute a hyperbolic tangent of a single argument expressed in radians.        
    )pbdoc");


#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}
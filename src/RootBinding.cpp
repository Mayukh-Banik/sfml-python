#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h> // for NumPy support
#include <nanobind/stl/vector.h>

#include "Audio.hpp"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(PROJECT_NAME, m)
{
    m.doc() = "This is a project wrapping C++ SFML for Python 3.8+";
    Audio(m);
}

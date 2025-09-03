#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h> // for NumPy support
#include <nanobind/stl/vector.h>

#include "Audio.hpp"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(PROJECT_NAME, m)
{
    m.doc() = "This is a \"hello world\" example with nanobind";
    m.def("div", [](int a, int b)
          { return a / b; }, "a"_a, "b"_a);

    AudioResource(m);
}

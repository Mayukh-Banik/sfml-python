#include <nanobind/nanobind.h>

namespace nb = nanobind;

using namespace nb::literals;

#include <SFML/Audio.hpp>

namespace nb = nanobind;

// void AudioResource(nb::module_& m)
// {
//     nb::class_<sf::SoundBuffer>(m, "SoundBuffer")
//     .def(nb::init<>())
//         ;
// }

class A
{
    public:
    A() = default;
    ~A() = default;
};

NB_MODULE(PROJECT_NAME, m) {
    m.doc() = "This is a \"hello world\" example with nanobind";
    m.def("div", [](int a, int b) {return a / b;}, "a", "b");
        nb::class_<A>(m, "SoundBuffer")
        .def(nb::init<>());
}

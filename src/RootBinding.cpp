#include "Audio.hpp"

using namespace nb::literals;

NB_MODULE(PROJECT_NAME, m)
{
    m.doc() = "This is a project wrapping C++ SFML for Python 3.8+";
    Audio(m);
}

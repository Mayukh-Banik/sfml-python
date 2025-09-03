#pragma once

#include <nanobind/nanobind.h>
#include "Audio/AudioResource.hpp"

void Audio(nb::module_& m)
{
    AudioResource(m);
}
#pragma once

#include <nanobind/nanobind.h>
#include "Audio/AudioResource.hpp"

void Audio(nb::module_& m)
{
    nb::module_ audioModule = m.def_submodule("Audio");
    AudioResource(audioModule);
}
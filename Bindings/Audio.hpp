#pragma once

#include <nanobind/nanobind.h>
namespace nb = nanobind;

#include "Audio/AudioResource.hpp"
#include "Audio/Export.hpp"
#include "Audio/InputSoundFile.hpp"

void Audio(nb::module_& m)
{
    nb::module_ audioModule = m.def_submodule("Audio", "Audio Submodule");
    AudioResource(audioModule);
    Export(audioModule);
    InputSoundFile(audioModule);
}
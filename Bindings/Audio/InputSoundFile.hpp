#pragma once

#include "SFML/Audio/InputSoundFile.hpp"
#include <nanobind/nanobind.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

void InputSoundFile(nb::module_ &m)
{
    nb::class_<sf::InputSoundFile>(m, "InputSoundFile")
        .def(nb::init<>())
        .def(nb::init<const std::filesystem::path &>(), nb::arg("filename"));
}
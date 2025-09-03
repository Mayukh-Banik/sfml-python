#pragma once

#include <SFML/Audio/SoundStream.hpp>
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void SoundStream(nb::module_ &m)
{
	nb::class_<sf::SoundStream>(m, "SoundStream")
		.def(nb::init<>())
        .def_rw("samples", &sf::SoundStream::Chunk::samples);
}
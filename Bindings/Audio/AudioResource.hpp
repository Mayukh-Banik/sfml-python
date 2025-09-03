#pragma once

#include <SFML/Audio/AudioResource.hpp>
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void AudioResource(nb::module_& m)
{
    nb::class_<sf::AudioResource>(m, "AudioResource")
        .def(nb::init<const sf::AudioResource&>()) 
        .def(nb::init<sf::AudioResource&&>())      
        ;
}
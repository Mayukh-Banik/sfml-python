#pragma once

#include <SFML/Audio/AudioResource.hpp>
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void AudioResource(nb::module_ &m)
{
	nb::class_<sf::AudioResource>(m, "AudioResource")
		.def(nb::init<const sf::AudioResource &>())
		.def(nb::init<sf::AudioResource &&>())
		.def("__copy__", [](const sf::AudioResource &self)
			 {
				 return std::make_shared<sf::AudioResource>(self); 
			 })
		.def("__deepcopy__", [](const sf::AudioResource &self, nb::dict)
			 { return std::make_shared<sf::AudioResource>(self); });
}
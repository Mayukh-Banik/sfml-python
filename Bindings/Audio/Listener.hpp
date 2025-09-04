#pragma once

#include "BaseHeader.hpp"

void Listener(nb::module_ &m)
{
    nb::module_ listener = m.def_submodule("Listener", "Listener Submodule");

    nb::class_<sf::Listener::Cone>(listener, "Cone")
        .def(nb::init<>())
        .def_rw("innerAngle", &sf::Listener::Cone::innerAngle)
        .def_rw("outerAngle", &sf::Listener::Cone::outerAngle)
        .def_rw("outerGain", &sf::Listener::Cone::outerGain);

    listener.def("setGlobalVolume", &sf::Listener::setGlobalVolume, nb::arg("volume"));
    listener.def("getGlobalVolume", &sf::Listener::getGlobalVolume);
    
    listener.def("setPosition", &sf::Listener::setPosition, nb::arg("position"));
    listener.def("getPosition", &sf::Listener::getPosition);
    
    listener.def("setDirection", &sf::Listener::setDirection, nb::arg("direction"));
    listener.def("getDirection", &sf::Listener::getDirection);
    
    listener.def("setVelocity", &sf::Listener::setVelocity, nb::arg("velocity"));
    listener.def("getVelocity", &sf::Listener::getVelocity);
    
    listener.def("setCone", &sf::Listener::setCone, nb::arg("cone"));
    listener.def("getCone", &sf::Listener::getCone);
    
    listener.def("setUpVector", &sf::Listener::setUpVector, nb::arg("upVector"));
    listener.def("getUpVector", &sf::Listener::getUpVector);
}
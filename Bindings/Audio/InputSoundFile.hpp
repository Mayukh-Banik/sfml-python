#pragma once

#include "BaseHeader.hpp"

namespace nb = nanobind;

void InputSoundFile(nb::module_ &m)
{
	nb::class_<sf::InputSoundFile>(m, "InputSoundFile")
		.def(nb::init<>())
		.def("__init__", [](sf::InputSoundFile *self, nb::bytes data)
			 {	const void* ptr = data.data();
				std::size_t size = data.size();
				new (self) sf::InputSoundFile(ptr, size); }, nb::arg("data"))
		.def(nb::init<const std::filesystem::path &>(), nb::arg("filename"))
		.def(nb::init<sf::InputStream &>(), nb::arg("stream"))
		.def("openFromFile", &sf::InputSoundFile::openFromFile, nb::arg("filename"))
		.def("openFromMemory", [](sf::InputSoundFile &self, nb::bytes data)
			 {	const void* ptr = data.data();
                std::size_t size = data.size();
				return self.openFromMemory(ptr, size); }, nb::arg("data"))
		.def("getSampleCount", &sf::InputSoundFile::getSampleCount)
		.def("getChannelCount", &sf::InputSoundFile::getChannelCount)
		.def("getChannelMap", &sf::InputSoundFile::getChannelMap)
		.def("getDuration", &sf::InputSoundFile::getDuration)
		.def("getTimeOffset", &sf::InputSoundFile::getTimeOffset)
		.def("getSampleOffset", &sf::InputSoundFile::getSampleOffset)
		.def("seek", nb::overload_cast<std::uint64_t>(&sf::InputSoundFile::seek), nb::arg("sampleOffset"))
		.def("seek", nb::overload_cast<sf::Time>(&sf::InputSoundFile::seek), nb::arg("timeOffset"))
		.def("read", &sf::InputSoundFile::read, nb::arg("samples"), nb::arg("maxCount"))
		.def("close", &sf::InputSoundFile::close);
}
module;

#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/shared_ptr.h>

export module Bindings;

namespace nb = nanobind;

void AudioResource(nb::module_ &m)
{
    nb::class_<sf::AudioResource>(m, "AudioResource")
        .def(nb::init<const sf::AudioResource &>())
        .def(nb::init<sf::AudioResource &&>())
        .def("__copy__", [](const sf::AudioResource &self)
             { return std::make_shared<sf::AudioResource>(self); })
        .def("__deepcopy__", [](const sf::AudioResource &self, nb::dict)
             { return std::make_shared<sf::AudioResource>(self); });
}

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

void Music(nb::module_ &m)
{
    nb::class_<sf::Music>(m, "Music")
        .def(nb::init<>())
        .def(nb::init<const std::filesystem::path &>(), nb::arg("filename"))
        .def("__init__", [](sf::Music *self, nb::bytes data)
             {	const void* ptr = data.data();
				std::size_t size = data.size();
				new (self) sf::Music(ptr, size); }, nb::arg("data"))
        .def(nb::init<sf::InputStream &>(), nb::arg("stream"))
        .def(nb::init<sf::Music &&>())
        .def("openFromFile", &sf::Music::openFromFile, nb::arg("filename"))
        .def("openFromMemory", [](sf::Music &self, nb::bytes data)
             {
                 const void *ptr = data.data();
                 std::size_t size = data.size();
                 return self.openFromMemory(ptr, size); }, nb::arg("data"))
        .def("openFromStream", &sf::Music::openFromStream, nb::arg("stream"))
        .def("getDuration", &sf::Music::getDuration)
        .def("getLoopPoints", &sf::Music::getLoopPoints)
        .def("setLoopPoints", &sf::Music::setLoopPoints, nb::arg("timePoints"))
        .def("play", &sf::Music::play)
        .def("pause", &sf::Music::pause)
        .def("stop", &sf::Music::stop)
        .def("getChannelCount", &sf::Music::getChannelCount)
        .def("getSampleRate", &sf::Music::getSampleRate)
        .def("getChannelMap", &sf::Music::getChannelMap)
        .def("getStatus", &sf::Music::getStatus)
        .def("setPlayingOffset", &sf::Music::setPlayingOffset, nb::arg("timeOffset"))
        .def("getPlayingOffset", &sf::Music::getPlayingOffset)
        .def("setLooping", &sf::Music::setLooping, nb::arg("loop"))
        .def("isLooping", &sf::Music::isLooping)
        .def("setEffectsProcessor", &sf::Music::setEffectProcessor, nb::arg("effectProcessor"))
        .def("setPitch", &sf::Music::setPitch, nb::arg("pitch"))
        .def("setPan", &sf::Music::setPan, nb::arg("pan"))
        .def("setVolume", &sf::Music::setVolume, nb::arg("volume"))
        .def("setSpatializationEnabled", &sf::Music::setSpatializationEnabled, nb::arg("enabled"))
        .def("setPosition", &sf::Music::setPosition, nb::arg("position"))
        .def("setDirection", &sf::Music::setDirection, nb::arg("direction"))
        .def("setCone", &sf::Music::setCone, nb::arg("cone"))
        .def("setVelocity", &sf::Music::setVelocity, nb::arg("velocity"))
        .def("setDopplerFactor", &sf::Music::setDopplerFactor, nb::arg("factor"))
        .def("setDirectionalAttenuationFactor", &sf::Music::setDirectionalAttenuationFactor, nb::arg("factor"))
        .def("setRelativeToListener", &sf::Music::setRelativeToListener, nb::arg("relative"))
        .def("setMinDistance", &sf::Music::setMinDistance, nb::arg("distance"))
        .def("setMaxDistance", &sf::Music::setMaxDistance, nb::arg("distance"))
        .def("setMinGain", &sf::Music::setMinGain, nb::arg("gain"))
        .def("setMaxGain", &sf::Music::setMaxGain, nb::arg("gain"))
        .def("setAttenuation", &sf::Music::setAttenuation, nb::arg("attenuation"))
        .def("getPitch", &sf::Music::getPitch)
        .def("getPan", &sf::Music::getPan)
        .def("getVolume", &sf::Music::getVolume)
        .def("isSpatializationEnabled", &sf::Music::isSpatializationEnabled)
        .def("getPosition", &sf::Music::getPosition)
        .def("getDirection", &sf::Music::getDirection)
        .def("getCone", &sf::Music::getCone)
        .def("getVelocity", &sf::Music::getVelocity)
        .def("getDopplerFactor", &sf::Music::getDopplerFactor)
        .def("getDirectionalAttenuationFactor", &sf::Music::getDirectionalAttenuationFactor)
        .def("isRelativeToListener", &sf::Music::isRelativeToListener)
        .def("getMinDistance", &sf::Music::getMinDistance)
        .def("getMaxDistance", &sf::Music::getMaxDistance)
        .def("getMinGain", &sf::Music::getMinGain)
        .def("getMaxGain", &sf::Music::getMaxGain)
        .def("getAttenuation", &sf::Music::getAttenuation);
}

void OutputSoundFile(nb::module_ &m)
{
    nb::class_<sf::OutputSoundFile>(m, "OutputSoundFile")
        // Default constructor
        .def(nb::init<>())

        // Parameterized constructor
        .def(nb::init<const std::filesystem::path &, unsigned int, unsigned int, const std::vector<sf::SoundChannel> &>(),
             nb::arg("filename"), nb::arg("sampleRate"), nb::arg("channelCount"), nb::arg("channelMap"))

        // openFromFile method
        .def("openFromFile", &sf::OutputSoundFile::openFromFile,
             nb::arg("filename"), nb::arg("sampleRate"), nb::arg("channelCount"), nb::arg("channelMap"))

        // write method - using lambda to handle raw pointer
        .def("write", [](sf::OutputSoundFile &self, nb::ndarray<nb::numpy, const std::int16_t> samples)
             { self.write(samples.data(), samples.size()); }, nb::arg("samples"))

        // Alternative write method if you want to accept Python list/buffer
        .def("write", [](sf::OutputSoundFile &self, const std::vector<std::int16_t> &samples)
             { self.write(samples.data(), samples.size()); }, nb::arg("samples"))

        // close method
        .def("close", &sf::OutputSoundFile::close);
}

void PlaybackDevice(nb::module_ &m)
{
    nb::module_ playback_device = m.def_submodule("PlaybackDevice", "PlaybackDevice Submodule");

    // Get available devices
    playback_device.def("getAvailableDevices", &sf::PlaybackDevice::getAvailableDevices);

    // Get default device
    playback_device.def("getDefaultDevice", &sf::PlaybackDevice::getDefaultDevice);

    // Set device
    playback_device.def("setDevice", &sf::PlaybackDevice::setDevice, nb::arg("name"));

    // Get current device
    playback_device.def("getDevice", &sf::PlaybackDevice::getDevice);
}

void Sound(nb::module_ &m)
{
    nb::class_<sf::Sound>(m, "Sound")
        // Constructor with SoundBuffer
        .def(nb::init<const sf::SoundBuffer &>(), nb::arg("buffer"))

        // Copy constructor
        .def(nb::init<const sf::Sound &>(), nb::arg("copy"))

        // Playback control methods
        .def("play", &sf::Sound::play)
        .def("pause", &sf::Sound::pause)
        .def("stop", &sf::Sound::stop)

        // Buffer management
        .def("setBuffer", static_cast<void (sf::Sound::*)(const sf::SoundBuffer &)>(&sf::Sound::setBuffer), nb::arg("buffer"))
        .def("getBuffer", &sf::Sound::getBuffer, nb::rv_policy::reference_internal)

        // Looping
        .def("setLooping", &sf::Sound::setLooping, nb::arg("loop"))
        .def("isLooping", &sf::Sound::isLooping)

        // Playing offset
        .def("setPlayingOffset", &sf::Sound::setPlayingOffset, nb::arg("timeOffset"))
        .def("getPlayingOffset", &sf::Sound::getPlayingOffset)

        // Effect processor
        .def("setEffectProcessor", &sf::Sound::setEffectProcessor, nb::arg("effectProcessor"))

        // Status
        .def("getStatus", &sf::Sound::getStatus);

    // Note: Assignment operator is automatically handled by nanobind for copy-assignable classes
}

void SoundBuffer(nb::module_ &m)
{
    nb::class_<sf::SoundBuffer>(m, "SoundBuffer")
        // Default constructor
        .def(nb::init<>())

        // Copy constructor
        .def(nb::init<const sf::SoundBuffer &>(), nb::arg("copy"))

        // Constructor from file
        .def(nb::init<const std::filesystem::path &>(), nb::arg("filename"))

        // Constructor from memory - using lambda for bytes support
        // .def(nb::init([](nb::bytes data) {
        //     return sf::SoundBuffer(data.data(), data.size());
        // }), nb::arg("data"))

        // Constructor from stream
        .def(nb::init<sf::InputStream &>(), nb::arg("stream"))

        // Constructor from samples - using lambda for array support
        // .def(nb::init([](nb::ndarray<nb::numpy, const std::int16_t> samples,
        //                 std::uint64_t sampleCount,
        //                 unsigned int channelCount,
        //                 unsigned int sampleRate,
        //                 const std::vector<sf::SoundChannel>& channelMap) {
        //     return sf::SoundBuffer(samples.data(), sampleCount, channelCount, sampleRate, channelMap);
        // }), nb::arg("samples"), nb::arg("sampleCount"), nb::arg("channelCount"),
        //     nb::arg("sampleRate"), nb::arg("channelMap"))

        // Load methods
        .def("loadFromFile", &sf::SoundBuffer::loadFromFile, nb::arg("filename"))

        .def("loadFromMemory", [](sf::SoundBuffer &self, nb::bytes data)
             { return self.loadFromMemory(data.data(), data.size()); }, nb::arg("data"))

        .def("loadFromStream", &sf::SoundBuffer::loadFromStream, nb::arg("stream"))

        .def("loadFromSamples", [](sf::SoundBuffer &self, nb::ndarray<nb::numpy, const std::int16_t> samples, std::uint64_t sampleCount, unsigned int channelCount, unsigned int sampleRate, const std::vector<sf::SoundChannel> &channelMap)
             { return self.loadFromSamples(samples.data(), sampleCount, channelCount, sampleRate, channelMap); }, nb::arg("samples"), nb::arg("sampleCount"), nb::arg("channelCount"), nb::arg("sampleRate"), nb::arg("channelMap"))

        // Save method
        .def("saveToFile", &sf::SoundBuffer::saveToFile, nb::arg("filename"))

        // Getters - getSamples returns array view
        // .def("getSamples", [](const sf::SoundBuffer& self) {
        //     const std::int16_t* samples = self.getSamples();
        //     std::uint64_t count = self.getSampleCount();
        //     return nb::ndarray<nb::numpy, const std::int16_t>(
        //         nb::handle(samples).inc_ref(), 1, new size_t[1]{static_cast<size_t>(count)});
        // })

        .def("getSampleCount", &sf::SoundBuffer::getSampleCount)
        .def("getSampleRate", &sf::SoundBuffer::getSampleRate)
        .def("getChannelCount", &sf::SoundBuffer::getChannelCount)
        .def("getChannelMap", &sf::SoundBuffer::getChannelMap)
        .def("getDuration", &sf::SoundBuffer::getDuration);

    // Assignment operator is handled automatically by nanobind
}

void SoundBufferRecorder(nb::module_ &m)
{
    nb::class_<sf::SoundBufferRecorder>(m, "SoundBufferRecorder")
        // Default constructor (implicitly available)
        .def(nb::init<>())

        // Public method
        .def("getBuffer", &sf::SoundBufferRecorder::getBuffer, nb::rv_policy::reference_internal);

    // Note: Protected virtual methods are not typically bound directly
    // as they're meant to be overridden in C++, not called from Python
}

void SoundChannel(nb::module_ &m)
{
    nb::enum_<sf::SoundChannel>(m, "SoundChannel")
        .value("Unspecified", sf::SoundChannel::Unspecified)
        .value("Mono", sf::SoundChannel::Mono)
        .value("FrontLeft", sf::SoundChannel::FrontLeft)
        .value("FrontRight", sf::SoundChannel::FrontRight)
        .value("FrontCenter", sf::SoundChannel::FrontCenter)
        .value("FrontLeftOfCenter", sf::SoundChannel::FrontLeftOfCenter)
        .value("FrontRightOfCenter", sf::SoundChannel::FrontRightOfCenter)
        .value("LowFrequencyEffects", sf::SoundChannel::LowFrequencyEffects)
        .value("BackLeft", sf::SoundChannel::BackLeft)
        .value("BackRight", sf::SoundChannel::BackRight)
        .value("BackCenter", sf::SoundChannel::BackCenter)
        .value("SideLeft", sf::SoundChannel::SideLeft)
        .value("SideRight", sf::SoundChannel::SideRight)
        .value("TopCenter", sf::SoundChannel::TopCenter)
        .value("TopFrontLeft", sf::SoundChannel::TopFrontLeft)
        .value("TopFrontRight", sf::SoundChannel::TopFrontRight)
        .value("TopFrontCenter", sf::SoundChannel::TopFrontCenter)
        .value("TopBackLeft", sf::SoundChannel::TopBackLeft)
        .value("TopBackRight", sf::SoundChannel::TopBackRight)
        .value("TopBackCenter", sf::SoundChannel::TopBackCenter);
}

void SoundFileFactory(nb::module_ &m)
{
    nb::class_<sf::SoundFileFactory>(m, "SoundFileFactory")
        // Template methods - you'll need to bind specific instantiations
        // Example: if you have specific reader/writer types like OggReader, WavReader, etc.
        // .def_static("registerOggReader", &sf::SoundFileFactory::registerReader<sf::priv::SoundFileReaderOgg>)
        // .def_static("unregisterOggReader", &sf::SoundFileFactory::unregisterReader<sf::priv::SoundFileReaderOgg>)
        // .def_static("isOggReaderRegistered", &sf::SoundFileFactory::isReaderRegistered<sf::priv::SoundFileReaderOgg>)

        // Non-template static methods
        .def_static("createReaderFromFilename", &sf::SoundFileFactory::createReaderFromFilename,
                    nb::arg("filename"))

        .def_static("createReaderFromMemory", [](nb::bytes data)
                    { return sf::SoundFileFactory::createReaderFromMemory(data.data(), data.size()); }, nb::arg("data"))

        .def_static("createReaderFromStream", &sf::SoundFileFactory::createReaderFromStream, nb::arg("stream"))

        .def_static("createWriterFromFilename", &sf::SoundFileFactory::createWriterFromFilename, nb::arg("filename"));
}

void SoundFileReader(nb::module_ &m)
{
    // First bind the nested Info struct
    nb::class_<sf::SoundFileReader::Info>(m, "SoundFileReaderInfo")
        .def(nb::init<>())
        .def_rw("sampleCount", &sf::SoundFileReader::Info::sampleCount)
        .def_rw("channelCount", &sf::SoundFileReader::Info::channelCount)
        .def_rw("sampleRate", &sf::SoundFileReader::Info::sampleRate)
        .def_rw("channelMap", &sf::SoundFileReader::Info::channelMap);

    // Bind the abstract base class
    nb::class_<sf::SoundFileReader>(m, "SoundFileReader")
        // Pure virtual methods - bind for potential Python subclassing
        .def("open", &sf::SoundFileReader::open, nb::arg("stream"))
        .def("seek", &sf::SoundFileReader::seek, nb::arg("sampleOffset"))

        // Read method - use lambda to handle array return
        .def("read", [](sf::SoundFileReader &self, std::uint64_t maxCount)
             {
            std::vector<std::int16_t> samples(maxCount);
            std::uint64_t actualCount = self.read(samples.data(), maxCount);
            samples.resize(actualCount);
            return samples; }, nb::arg("maxCount"));
}

void SoundFileWriter(nb::module_ &m)
{
    nb::class_<sf::SoundFileWriter>(m, "SoundFileWriter")
        // Open method
        .def("open", &sf::SoundFileWriter::open,
             nb::arg("filename"), nb::arg("sampleRate"), nb::arg("channelCount"), nb::arg("channelMap"))

        // Write method - using lambda to handle different input types
        .def("write", [](sf::SoundFileWriter &self, nb::ndarray<nb::numpy, const std::int16_t> samples)
             { self.write(samples.data(), samples.size()); }, nb::arg("samples"))

        // Alternative write method for Python lists/vectors
        .def("write", [](sf::SoundFileWriter &self, const std::vector<std::int16_t> &samples)
             { self.write(samples.data(), samples.size()); }, nb::arg("samples"));
}

void SoundRecorder(nb::module_ &m)
{
    nb::class_<sf::SoundRecorder>(m, "SoundRecorder")
        // Public methods
        .def("start", &sf::SoundRecorder::start, nb::arg("sampleRate") = 44100)
        .def("stop", &sf::SoundRecorder::stop)
        .def("getSampleRate", &sf::SoundRecorder::getSampleRate)

        // Device management
        .def("setDevice", &sf::SoundRecorder::setDevice, nb::arg("name"))
        .def("getDevice", &sf::SoundRecorder::getDevice, nb::rv_policy::reference_internal)

        // Channel management
        .def("setChannelCount", &sf::SoundRecorder::setChannelCount, nb::arg("channelCount"))
        .def("getChannelCount", &sf::SoundRecorder::getChannelCount)
        .def("getChannelMap", &sf::SoundRecorder::getChannelMap, nb::rv_policy::reference_internal)

        // Static methods
        .def_static("getAvailableDevices", &sf::SoundRecorder::getAvailableDevices)
        .def_static("getDefaultDevice", &sf::SoundRecorder::getDefaultDevice)
        .def_static("isAvailable", &sf::SoundRecorder::isAvailable);

    // Note: Protected constructor and virtual methods are not bound directly
    // since this is an abstract base class meant to be subclassed in C++
}

void SoundSource(nb::module_ &m)
{
    // First bind the Status enum
    nb::enum_<sf::SoundSource::Status>(m, "SoundSourceStatus")
        .value("Stopped", sf::SoundSource::Status::Stopped)
        .value("Paused", sf::SoundSource::Status::Paused)
        .value("Playing", sf::SoundSource::Status::Playing);

    // Bind the Cone struct
    nb::class_<sf::SoundSource::Cone>(m, "SoundSourceCone")
        .def(nb::init<>())
        .def_rw("innerAngle", &sf::SoundSource::Cone::innerAngle)
        .def_rw("outerAngle", &sf::SoundSource::Cone::outerAngle)
        .def_rw("outerGain", &sf::SoundSource::Cone::outerGain);

    // Bind the EffectProcessor type alias (as a callback)
    nb::class_<sf::SoundSource::EffectProcessor>(m, "EffectProcessor");

    // Bind the main SoundSource class
    nb::class_<sf::SoundSource>(m, "SoundSource")
        // Setters
        .def("setPitch", &sf::SoundSource::setPitch, nb::arg("pitch"))
        .def("setPan", &sf::SoundSource::setPan, nb::arg("pan"))
        .def("setVolume", &sf::SoundSource::setVolume, nb::arg("volume"))
        .def("setSpatializationEnabled", &sf::SoundSource::setSpatializationEnabled, nb::arg("enabled"))
        .def("setPosition", &sf::SoundSource::setPosition, nb::arg("position"))
        .def("setDirection", &sf::SoundSource::setDirection, nb::arg("direction"))
        .def("setCone", &sf::SoundSource::setCone, nb::arg("cone"))
        .def("setVelocity", &sf::SoundSource::setVelocity, nb::arg("velocity"))
        .def("setDopplerFactor", &sf::SoundSource::setDopplerFactor, nb::arg("factor"))
        .def("setDirectionalAttenuationFactor", &sf::SoundSource::setDirectionalAttenuationFactor, nb::arg("factor"))
        .def("setRelativeToListener", &sf::SoundSource::setRelativeToListener, nb::arg("relative"))
        .def("setMinDistance", &sf::SoundSource::setMinDistance, nb::arg("distance"))
        .def("setMaxDistance", &sf::SoundSource::setMaxDistance, nb::arg("distance"))
        .def("setMinGain", &sf::SoundSource::setMinGain, nb::arg("gain"))
        .def("setMaxGain", &sf::SoundSource::setMaxGain, nb::arg("gain"))
        .def("setAttenuation", &sf::SoundSource::setAttenuation, nb::arg("attenuation"))

        // EffectProcessor - using lambda for Python callable support
        .def("setEffectProcessor", [](sf::SoundSource &self, nb::callable processor)
             {
            sf::SoundSource::EffectProcessor cpp_processor = [processor](
                const float* inputFrames, unsigned int& inputFrameCount,
                float* outputFrames, unsigned int& outputFrameCount,
                unsigned int frameChannelCount) {
                // Convert to Python-friendly types and call
                processor(inputFrames, inputFrameCount, outputFrames, outputFrameCount, frameChannelCount);
            };
            self.setEffectProcessor(cpp_processor); }, nb::arg("effectProcessor"))

        // Getters
        .def("getPitch", &sf::SoundSource::getPitch)
        .def("getPan", &sf::SoundSource::getPan)
        .def("getVolume", &sf::SoundSource::getVolume)
        .def("isSpatializationEnabled", &sf::SoundSource::isSpatializationEnabled)
        .def("getPosition", &sf::SoundSource::getPosition)
        .def("getDirection", &sf::SoundSource::getDirection)
        .def("getCone", &sf::SoundSource::getCone)
        .def("getVelocity", &sf::SoundSource::getVelocity)
        .def("getDopplerFactor", &sf::SoundSource::getDopplerFactor)
        .def("getDirectionalAttenuationFactor", &sf::SoundSource::getDirectionalAttenuationFactor)
        .def("isRelativeToListener", &sf::SoundSource::isRelativeToListener)
        .def("getMinDistance", &sf::SoundSource::getMinDistance)
        .def("getMaxDistance", &sf::SoundSource::getMaxDistance)
        .def("getMinGain", &sf::SoundSource::getMinGain)
        .def("getMaxGain", &sf::SoundSource::getMaxGain)
        .def("getAttenuation", &sf::SoundSource::getAttenuation)

        // Pure virtual methods (for subclasses)
        .def("play", &sf::SoundSource::play)
        .def("pause", &sf::SoundSource::pause)
        .def("stop", &sf::SoundSource::stop)
        .def("getStatus", &sf::SoundSource::getStatus);

    // Note: Protected constructor and private methods are not bound
    // Assignment operators are handled automatically by nanobind
}

void SoundStream(nb::module_ &m)
{
    // First bind the Chunk struct
    nb::class_<sf::SoundStream::Chunk>(m, "SoundStreamChunk")
        .def(nb::init<>())
        .def_rw("samples", &sf::SoundStream::Chunk::samples)
        .def_rw("sampleCount", &sf::SoundStream::Chunk::sampleCount);

    // Bind the main SoundStream class
    nb::class_<sf::SoundStream>(m, "SoundStream")
        // Public methods (inherited from SoundSource and overridden)
        .def("play", &sf::SoundStream::play)
        .def("pause", &sf::SoundStream::pause)
        .def("stop", &sf::SoundStream::stop)
        .def("getStatus", &sf::SoundStream::getStatus)

        // SoundStream-specific methods
        .def("getChannelCount", &sf::SoundStream::getChannelCount)
        .def("getSampleRate", &sf::SoundStream::getSampleRate)
        .def("getChannelMap", &sf::SoundStream::getChannelMap)

        // Playback control
        .def("setPlayingOffset", &sf::SoundStream::setPlayingOffset, nb::arg("timeOffset"))
        .def("getPlayingOffset", &sf::SoundStream::getPlayingOffset)

        // Looping
        .def("setLooping", &sf::SoundStream::setLooping, nb::arg("loop"))
        .def("isLooping", &sf::SoundStream::isLooping)

        // Effect processor
        .def("setEffectProcessor", [](sf::SoundStream &self, nb::callable processor)
             {
            sf::SoundSource::EffectProcessor cpp_processor = [processor](
                const float* inputFrames, unsigned int& inputFrameCount,
                float* outputFrames, unsigned int& outputFrameCount,
                unsigned int frameChannelCount) {
                processor(inputFrames, inputFrameCount, outputFrames, outputFrameCount, frameChannelCount);
            };
            self.setEffectProcessor(cpp_processor); }, nb::arg("effectProcessor"));

    // Note: Protected constructor and virtual methods are not bound directly
    // since this is an abstract base class meant to be subclassed in C++

    // Move constructor and assignment operator are handled automatically
}

export void Audio(nb::module_ &m)
{
    auto& audioModule = m;
    AudioResource(audioModule);
    InputSoundFile(audioModule);
    Listener(audioModule);
    Music(audioModule);
    OutputSoundFile(audioModule);
    PlaybackDevice(audioModule);
    Sound(audioModule);
    SoundBuffer(audioModule);
    SoundBufferRecorder(audioModule);
    SoundChannel(audioModule);
    SoundFileFactory(audioModule);
    SoundFileReader(audioModule);
    SoundFileWriter(audioModule);
    SoundRecorder(audioModule);
    SoundSource(audioModule);
    SoundStream(audioModule);
}
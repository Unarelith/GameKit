/*
 * =====================================================================================
 *
 *       Filename:  AudioPlayer.cpp
 *
 *    Description:
 *
 *        Created:  28/04/2015 21:52:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Audio/Sound.hpp>

#include "gk/resource/AudioPlayer.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

bool AudioPlayer::s_muteState = false;
sf::Music *AudioPlayer::s_currentMusic = nullptr;

void AudioPlayer::playMusic(const std::string &resourceName) {
	s_currentMusic = &ResourceHandler::getInstance().get<sf::Music>(resourceName);
	if (!s_muteState)
		s_currentMusic->play();
}

void AudioPlayer::playSound(const std::string &resourceName) {
	if (!s_muteState)
		ResourceHandler::getInstance().get<sf::Sound>(resourceName).play();
}

void AudioPlayer::repeatSound(const std::string &, u8) {
	// FIXME
	// if (!s_muteState)
	// 	ResourceHandler::getInstance().get<sf::Sound>(resourceName).repeat(delay);
}

void AudioPlayer::pauseMusic() {
	if (s_currentMusic)
		s_currentMusic->pause();
}

void AudioPlayer::resumeMusic() {
	if (s_currentMusic)
		s_currentMusic->play();
}

bool AudioPlayer::isMusicPaused() {
	return s_currentMusic ? s_currentMusic->getStatus() == sf::Music::Paused : false;
}

bool AudioPlayer::isMusicPlaying() {
	return s_currentMusic ? s_currentMusic->getStatus() == sf::Music::Playing : false;
}

} // namespace gk


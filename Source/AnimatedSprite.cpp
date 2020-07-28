#include "AnimatedSprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(sf::Texture& texture, int numberOfFrames, sf::Time&& timePerFrame, bool isLooped)
	: m_texture(texture), m_isLooped(isLooped), m_numberOfFrames(numberOfFrames), m_currentFrame(0), m_timePerFrame(timePerFrame)
{

	m_frameWidth = texture.getSize().x / numberOfFrames;
	m_frameHeight = texture.getSize().y;

	for(std::size_t i = 0; i < numberOfFrames; ++i) {
		sf::IntRect rect;

		rect.top = 0;
		rect.left = i * m_frameWidth;
		rect.height = m_frameHeight;
		rect.width = m_frameWidth;

		m_frames.push_back(rect);
	}
}

void AnimatedSprite::update(sf::Time& dt) {
	m_currentTime += dt;

	if (m_isLooped && m_currentTime.asSeconds() >= m_timePerFrame.asSeconds() * m_numberOfFrames)
		m_currentTime = sf::seconds(0.f);

	m_currentFrame = std::fminf(std::floor(m_currentTime.asSeconds() / m_timePerFrame.asSeconds()), m_numberOfFrames - 1);
}

sf::IntRect AnimatedSprite::getFrame() const {
	return m_frames[m_currentFrame];
}
#pragma once

#include "SFML/Graphics.hpp"

class AnimatedSprite : public sf::Transformable {
public:
	AnimatedSprite(sf::Texture& texture, int numberOfFrames, sf::Time&& timePerFrame = sf::seconds(0.1f), bool isLooped = true);

	void update(sf::Time& dt);
	sf::IntRect getFrame() const;

private:

private:
	const sf::Texture& m_texture;
	std::vector<sf::IntRect> m_frames;

	bool m_isLooped;
	int m_numberOfFrames;
	int m_currentFrame;

	sf::Time m_timePerFrame;
	sf::Time m_currentTime;

	size_t m_frameWidth;
	size_t m_frameHeight;
};


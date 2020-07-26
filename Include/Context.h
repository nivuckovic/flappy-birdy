#pragma once

#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"

class Flappy;

struct Context {
	Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder)
		: m_window(window), m_textureHolder(textureHolder), m_fontHolder(fontHolder) {};
	
	sf::RenderWindow& m_window;
	TextureHolder& m_textureHolder;
	FontHolder& m_fontHolder;
};
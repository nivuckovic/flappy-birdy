#include "Background.h"
#include "..\Include\Background.h"

Background::Background(Context& context, GameObjectType type) : GameObject(context, type), m_view(0, 0) {
	m_sprite.setTexture(context.m_textureHolder.get(ID::Textures::BACKGROUND));
	m_sprite.setTextureRect(sf::IntRect(m_view.x, m_view.y, 801, 801));
}

void Background::update(sf::Time& dt) {
	m_view.x += 2;

	m_sprite.setTextureRect(sf::IntRect(m_view.x, m_view.y, 800, 800));
}

void Background::input(sf::Event& event) {
}

void Background::render() {
	getContext().m_window.draw(m_sprite);
}

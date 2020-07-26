#include "Obstacle.h"

#include "RNG.h"

Obstacle::Obstacle(Context& context, GameObjectType type) : GameObject(context, type), m_offset(200.f), m_velocity(-3.f, 0.f), m_spawnPositionX(900), m_obstacleWidth(38.f), m_passedPlayer(false) {
	float height = RNG::getInstance().getFloatNumber(50.f, 550.f);

	m_top.setTexture(&getContext().m_textureHolder.get(ID::Textures::OBSTACLE), true);
	m_top.setPosition(m_spawnPositionX, 0.f);
	m_top.setSize(sf::Vector2f(m_obstacleWidth, height));
	m_top.setTextureRect(sf::IntRect(0, 0, m_top.getSize().x, m_top.getSize().y));

	m_bottom.setTexture(&getContext().m_textureHolder.get(ID::Textures::OBSTACLE), true);
	m_bottom.setPosition(m_spawnPositionX, height + m_offset);
	m_bottom.setSize(sf::Vector2f(m_obstacleWidth, 800.f));
	m_bottom.setTextureRect(sf::IntRect(0, 0, m_bottom.getSize().x, m_bottom.getSize().y));
}

void Obstacle::update(sf::Time& dt) {
	if (!isPlayable())
		return;

	setPositionTop(getPositionTop() + m_velocity);
	setPositionBottom(getPositionBottom() + m_velocity);

	if (isOutside()) {
		setDisposed();
	}
}

void Obstacle::render() {
	getContext().m_window.draw(m_bottom);
	getContext().m_window.draw(m_top);
}

void Obstacle::input(sf::Event& event) {

}

bool Obstacle::isOutside() {
	return getPositionBottom().x + m_obstacleWidth < 0 ? true : false;
}

void Obstacle::setPositionTop(sf::Vector2f pos) {
	m_top.setPosition(pos);
}

void Obstacle::setPositionBottom(sf::Vector2f pos) {
	m_bottom.setPosition(pos);
}

sf::Vector2f Obstacle::getPositionTop() const {
	return m_top.getPosition();
}

sf::Vector2f Obstacle::getPositionBottom() const {
	return m_bottom.getPosition();
}

sf::Vector2f Obstacle::getSizeTop() const {
	return m_top.getSize();
}

sf::Vector2f Obstacle::getSizeBottom() const {
	return m_bottom.getSize();
}

void Obstacle::passPlayer() {
	m_passedPlayer = true;
}

bool Obstacle::isPlayerPassed() const {
	return m_passedPlayer;
}

#include "Obstacle.h"

#include "RNG.h"

Obstacle::Obstacle(Context& context, GameObjectType type) : GameObject(context, type), m_offset(200.f), m_velocity(-3.f, 0.f), m_spawnPositionX(900), m_obstacleWidth(38.f), m_passedPlayer(false), m_texture(getContext().m_textureHolder.get(ID::Textures::OBSTACLE)) {
	float height = RNG::getInstance().getFloatNumber(50.f, 550.f);

	// m_top.setTexture(&getContext().m_textureHolder.get(ID::Textures::OBSTACLE), true);
	m_top.setPosition(m_spawnPositionX, 0.f);
	m_top.setSize(sf::Vector2f(m_obstacleWidth, height));
	m_top.setTextureRect(sf::IntRect(0, 0, m_top.getSize().x, m_top.getSize().y));

	// m_bottom.setTexture(&getContext().m_textureHolder.get(ID::Textures::OBSTACLE), true);
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
	sf::RenderWindow& window = getContext().m_window;
	sf::RenderStates states;

	sf::VertexArray m_top1(sf::Quads, 4);
	sf::VertexArray m_top2(sf::Quads, 4);

	sf::VertexArray m_bottom1(sf::Quads, 4);
	sf::VertexArray m_bottom2(sf::Quads, 4);

	float pipeHeight = 22.f;

	float left = m_top.getPosition().x;
	float right = left + m_top.getSize().x;
	float top = m_top.getPosition().y;
	float bottom = top + m_top.getSize().y;

	// gornji dio gornje cijevi
	m_top1[0].position = sf::Vector2f(left, top);
	m_top1[1].position = sf::Vector2f(right, top);
	m_top1[2].position = sf::Vector2f(right, bottom - pipeHeight);
	m_top1[3].position = sf::Vector2f(left, bottom - pipeHeight);

	m_top1[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_top1[1].texCoords = sf::Vector2f(38.f, 0.f);
	m_top1[2].texCoords = sf::Vector2f(38.f, 34.f);
	m_top1[3].texCoords = sf::Vector2f(0.f, 34.f);

	// donji dio gornje cijevi
	m_top2[0].position = sf::Vector2f(left, bottom - pipeHeight);
	m_top2[1].position = sf::Vector2f(right, bottom - pipeHeight);
	m_top2[2].position = sf::Vector2f(right, bottom);
	m_top2[3].position = sf::Vector2f(left, bottom);

	m_top2[0].texCoords = sf::Vector2f(0.f, 34.f);
	m_top2[1].texCoords = sf::Vector2f(38.f, 34.f);
	m_top2[2].texCoords = sf::Vector2f(38.f, 56.f);
	m_top2[3].texCoords = sf::Vector2f(0.f, 56.f);

	left = m_bottom.getPosition().x;
	right = left + m_bottom.getSize().x;
	top = m_bottom.getPosition().y;
	bottom = top + m_bottom.getSize().y;

	// donji dio donje cijevi
	m_bottom1[2].position = sf::Vector2f(left, top + pipeHeight);
	m_bottom1[3].position = sf::Vector2f(right, top + pipeHeight);
	m_bottom1[0].position = sf::Vector2f(right, bottom);
	m_bottom1[1].position = sf::Vector2f(left, bottom);

	m_bottom1[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_bottom1[1].texCoords = sf::Vector2f(38.f, 0.f);
	m_bottom1[2].texCoords = sf::Vector2f(38.f, 34.f);
	m_bottom1[3].texCoords = sf::Vector2f(0.f, 34.f);

	// gornji dio donje cijevi
	m_bottom2[2].position = sf::Vector2f(left, top);
	m_bottom2[3].position = sf::Vector2f(right, top);
	m_bottom2[0].position = sf::Vector2f(right, top + pipeHeight);
	m_bottom2[1].position = sf::Vector2f(left, top + pipeHeight);

	m_bottom2[0].texCoords = sf::Vector2f(0.f, 34.f);
	m_bottom2[1].texCoords = sf::Vector2f(38.f, 34.f);
	m_bottom2[2].texCoords = sf::Vector2f(38.f, 56.f);
	m_bottom2[3].texCoords = sf::Vector2f(0.f, 56.f);

	states.texture = &m_texture;

	window.draw(m_top1, states);
	window.draw(m_top2, states);

	window.draw(m_bottom1, states);
	window.draw(m_bottom2, states);
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

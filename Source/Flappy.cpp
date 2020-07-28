#include "Flappy.h"


Flappy::Flappy(Context& context, GameObjectType type) 
	: GameObject(context, type), m_flyingAnimation(getContext().m_textureHolder.get(ID::Textures::FLAPPY), 3), m_gravity(0.f, 0.2f), m_sprite(25.f), m_jumpPressed(false), m_particleSystem(30), m_playing(false)
{
	m_sprite.setTexture(&getContext().m_textureHolder.get(ID::Textures::FLAPPY));
	setPosition(sf::Vector2f(100.f, 400.f));
}

void Flappy::update(sf::Time& dt) {
	if (isJumpPressed())
		jump();
	
	updateAnimation(dt);
	rotateFlappy();

	m_particleSystem.setEmitter(getPosition() + sf::Vector2f(getCollider().getRadius() / 2, getCollider().getRadius() / 2));
	m_particleSystem.update(dt);

	if (m_playing == false)
		return;

	addVelocity(m_gravity);
	setPosition(getPosition() + getVelocity());
}

void Flappy::render() {
	m_particleSystem.draw(getContext().m_window);
	getContext().m_window.draw(m_sprite);
}

void Flappy::input(sf::Event& event) {
	if (!isPlayable())
		return;

	if (event.type == sf::Event::MouseButtonPressed) {
		jump();
	}
}

void Flappy::setPosition(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}

void Flappy::setVelocity(sf::Vector2f vel) {
	m_velocity.x = vel.x;
	m_velocity.y = std::fminf(vel.y, 10.f);
}

void Flappy::setAcceleration(sf::Vector2f acc) {
	m_acceleration = acc;
}

sf::Vector2f Flappy::getPosition() const
{
	return m_sprite.getPosition();
}

sf::Vector2f Flappy::getVelocity() const
{
	return m_velocity;
}

sf::Vector2f Flappy::getAcceleration() const
{
	return m_acceleration;
}

sf::CircleShape Flappy::getCollider() const {
	return m_sprite;
}

void Flappy::addVelocity(sf::Vector2f vel) {
	setVelocity(getVelocity() + vel);
}

void Flappy::jump() {
	if (getVelocity().y >= 0) {
		m_playing = true;
		setVelocity(sf::Vector2f(0.f, -7.f));
	}

	setJumpPressed(false);
}

void Flappy::onCollisionEnter() {
	m_sprite.setFillColor(sf::Color::Red);
}

void Flappy::setJumpPressed(bool val) {
	m_jumpPressed = val;
}

bool Flappy::isJumpPressed() const {
	return m_jumpPressed;
}

void Flappy::updateAnimation(sf::Time& dt) {
	m_flyingAnimation.update(dt);
	m_sprite.setTextureRect(m_flyingAnimation.getFrame());
}

void Flappy::rotateFlappy() {
	// dodati
}

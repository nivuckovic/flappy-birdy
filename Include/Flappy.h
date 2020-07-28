#pragma once

#include "SFML/Graphics.hpp"

#include "GameObject.h"
#include "ParticleSystem.h"
#include "AnimatedSprite.h"

class Flappy : public GameObject {
public:
	Flappy(Context& context, GameObjectType type);

	void update(sf::Time& dt) override;
	void render() override;
	void input(sf::Event& event) override;

	void setPosition(sf::Vector2f pos);
	void setVelocity(sf::Vector2f vel);
	void setAcceleration(sf::Vector2f acc);

	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getAcceleration() const;

	sf::CircleShape getCollider() const;

	void addVelocity(sf::Vector2f vel);

	void jump();
	void onCollisionEnter();

	void setJumpPressed(bool val);
	bool isJumpPressed() const;

private:
	void updateAnimation(sf::Time& dt);
	void rotateFlappy();

private:
	sf::CircleShape m_sprite;
	ParticleSystem m_particleSystem;
	AnimatedSprite m_flyingAnimation;

	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_gravity;

	bool m_jumpPressed;
	bool m_playing;
};

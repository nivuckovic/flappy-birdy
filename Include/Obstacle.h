#pragma once

#include "SFML/Graphics.hpp"

#include "GameObject.h"
#include "Context.h"


class Obstacle : public GameObject {
public:
	Obstacle(Context& context, GameObjectType type);

	void update(sf::Time& dt) override;
	void render() override;
	void input(sf::Event& event) override;

	bool isOutside();

	void setPositionTop(sf::Vector2f pos);
	void setPositionBottom(sf::Vector2f pos);

	sf::Vector2f getPositionTop() const;
	sf::Vector2f getPositionBottom() const;

	sf::Vector2f getSizeTop() const;
	sf::Vector2f getSizeBottom() const;

	void passPlayer();
	bool isPlayerPassed() const;

private:
	sf::RectangleShape m_bottom;
	sf::RectangleShape m_top;

	float m_offset;
	float m_spawnPositionX;
	float m_obstacleWidth;

	sf::Vector2f m_velocity;
	
	bool m_passedPlayer;
};
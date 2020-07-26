#pragma once

#include "SFML/Graphics.hpp"

class ParticleSystem {
public:
	ParticleSystem(int count);

	void setEmitter(sf::Vector2f pos);

	void update(sf::Time& dt);
	void draw(sf::RenderWindow& window);

	void start();

private:
	struct Particle {
		sf::Vector2f m_velocity;
		sf::Time m_lifeTime;
	};

	void resetParticle(int index);

private:
	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	
	sf::Time m_lifeTime;
	sf::Vector2f m_emitter;
};


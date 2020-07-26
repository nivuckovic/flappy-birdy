#include "ParticleSystem.h"
#include "..\Include\ParticleSystem.h"

#include "RNG.h"
#include <iostream>

ParticleSystem::ParticleSystem(int count) 
	: m_particles(count * 3), m_vertices(sf::Triangles, count * 3), m_lifeTime(sf::seconds(1.5f)), m_emitter(0.f, 0.f)
{

}

void ParticleSystem::setEmitter(sf::Vector2f pos) {
	m_emitter = pos;
}

void ParticleSystem::update(sf::Time& dt) {
	for (int i = 0; i < m_particles.size(); i = i + 3) {
		

		for (std::size_t j = 0; j < 3; ++j) {
			Particle& p = m_particles[i + j];

			if (!(i % 3) && p.m_lifeTime <= sf::Time::Zero)
				resetParticle(i);

			p.m_lifeTime -= dt;

			m_vertices[i + j].position += p.m_velocity;

			float ratio = p.m_lifeTime.asSeconds() / m_lifeTime.asSeconds();
			m_vertices[i + j].color.a = static_cast<sf::Uint8> (ratio * 255);
		}
	}
}

void ParticleSystem::draw(sf::RenderWindow& window) {
	window.draw(m_vertices);
}

void ParticleSystem::start() {
	for (std::size_t i = 0; i < m_particles.size(); i = i + 3)
		resetParticle(i);
}

void ParticleSystem::resetParticle(int index) {
	float angle = ((RNG::getInstance().getFloatNumber(0, 90) + 135.f) * 3.14f / 180.f);
	float speed = RNG::getInstance().getFloatNumber(3.f, 4.f);

	int color = RNG::getInstance().getIntegerNumber(0, 2);

	for (std::size_t i = 0; i < 3; ++i) {
		m_particles[index + i].m_velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index + i].m_lifeTime = sf::milliseconds(RNG::getInstance().getIntegerNumber(0, m_lifeTime.asMilliseconds()));

		// zamjeni s enumima..
		switch (color) {
		case 0:
			m_vertices[index + i].color = sf::Color::Magenta;
			break;
		case 1:
			m_vertices[index + i].color = sf::Color::Blue;
			break;
		case 2:
			m_vertices[index + i].color = sf::Color::Red;
			break;
		default:
			break;
		}
	}

	float rotation = (RNG::getInstance().getFloatNumber(0, 360) * 3.14f / 180.f);
	float radius = RNG::getInstance().getIntegerNumber(4, 20);

	m_vertices[index].position = m_emitter + sf::Vector2f(std::cos(rotation) * radius, std::sin(rotation) * radius);
	m_vertices[index + 1].position = m_emitter + sf::Vector2f(std::cos(rotation + 3.14f / 3) * radius, std::sin(rotation + 3.14f / 3) * radius);
	m_vertices[index + 2].position = m_emitter + sf::Vector2f(std::cos(rotation + 2 * 3.14f / 3) * radius, std::sin(rotation + 2 * 3.14f / 3) * radius);
}

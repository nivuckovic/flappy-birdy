#pragma once

struct Cooldown {
	Cooldown(float t) : m_cooldown(sf::seconds(t)), m_elapsed(sf::seconds(0.f)) {}

	bool isReady(sf::Time& dt) {
		m_elapsed += dt;

		if (m_elapsed >= m_cooldown) {
			m_elapsed = sf::seconds(0.f);

			return true;
		}

		return false;
	}

	void restart() {
		m_elapsed = sf::seconds(0.f);
	}

	sf::Time m_cooldown;
	sf::Time m_elapsed;
};
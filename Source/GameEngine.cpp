#include "GameEngine.h"
#include "..\Include\GameEngine.h"

#include "State.h"
#include "PlayingState.h"

GameEngine::GameEngine() : m_window(sf::VideoMode(800, 800), "Flappy Bird Clone"), m_context(m_window, m_textureHolder, m_fontHolder) {
	m_window.setFramerateLimit(60.f);

	std::unique_ptr<PlayingState> playingStatePtr(new PlayingState(m_context));
	m_stateStack.push_back(std::move(playingStatePtr));
}

void GameEngine::run() {
	while (m_window.isOpen()) {
		input();
		update(m_clock.restart());
		render();
	}
}

void GameEngine::input() {
	sf::Event m_event;
	
	while (m_window.pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed)
			m_window.close();

		for (auto& state : m_stateStack) {
			state->input(m_event);
		}
	}
}

void GameEngine::update(sf::Time&& dt) {
	for (auto& state : m_stateStack) {
		state->update(dt);
	}
}

void GameEngine::render() {
	m_window.clear();

	for (auto& state : m_stateStack) {
		state->render();
	}

	m_window.display();
}

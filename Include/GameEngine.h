#pragma once

#include <vector>
#include <memory>

#include "Context.h"
#include "State.h"
#include "Enums.h"

class GameEngine {
public:
	GameEngine();

	void run();

	void input();
	void update(sf::Time&& dt);
	void render();

private:
	Context m_context;

	sf::RenderWindow m_window;
	TextureHolder m_textureHolder;
	FontHolder m_fontHolder;

	sf::Clock m_clock;

	std::vector<std::unique_ptr<State>> m_stateStack;
	std::vector<StateStack::Action> m_pendingActions;
};


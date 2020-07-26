#pragma once
#include "State.h"

#include "Cooldown.h"

class Flappy;

class PlayingState : public State {
public:
	PlayingState(Context& context);

	bool input(sf::Event& event) override;
	bool update(sf::Time& dt) override;
	bool render() override;

	void increaseScore(int val = 1);

	void setGameOver(bool val);
	bool isGameOver() const;

	void setGameStarted(bool val);
	bool isGameStarted() const;

	void restart();

	void loadResources() override;

private:
	bool checkCollision(Flappy& player, sf::Vector2f pos, sf::Vector2f size);

	void createScene();
	void createPlayer();
	void disposeObjects();
	void createObstacles(sf::Time& dt);
	void onGameOver();

	void updateObjects(sf::Time& dt, GameObjectType type = GameObjectType::LENGTH);
	void renderUI();
private:
	Flappy* m_player;

	sf::Text m_scoreText;
	sf::Text m_startText;

	Cooldown m_obstacleSpawnCooldown;

	int m_score;
	bool m_gameOver;
	bool m_gameStarted;
};


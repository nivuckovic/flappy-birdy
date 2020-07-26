#include "PlayingState.h"

#include "Flappy.h"
#include "Obstacle.h"
#include "Background.h"

#include <iostream>
#include <string>

PlayingState::PlayingState(Context& context) : State(context), m_obstacleSpawnCooldown(2.25f), m_score(0), m_gameOver(false), m_gameStarted(false) {
	loadResources();
	createScene();

	m_scoreText.setFont(getContext().m_fontHolder.get(ID::Fonts::ARIAL));
	m_scoreText.setString("Score: " + std::to_string(m_score));

	m_startText.setFont(getContext().m_fontHolder.get(ID::Fonts::ARIAL));
	m_startText.setString("Press JUMP to start the game!!!");
	m_startText.setPosition(200.f, 380.f);

}

bool PlayingState::input(sf::Event& event) {
	if (!isGameStarted() && event.type == sf::Event::MouseButtonPressed) {
		setGameStarted(true);
	}

	for (auto& object : m_objects)
		object.get()->input(event);
	
	return false;
}

bool PlayingState::update(sf::Time& dt) {
	if (isGameOver()) {
		onGameOver();
		updateObjects(dt, GameObjectType::PLAYER);
	}
	else {
		updateObjects(dt);

		if (isGameStarted()) {
			for (auto& obstacle : getObjectsByType(GameObjectType::OBSTACLE)) {
				Obstacle* obs = dynamic_cast<Obstacle*>(obstacle);

				// Van mape
				if (m_player->getPosition().y < 0 || m_player->getPosition().y + m_player->getCollider().getRadius() > 800.f) {
					m_player->onCollisionEnter();
					setGameOver(true);
				}

				// Provjeri koliziju
				if (checkCollision(*m_player, obs->getPositionTop(), obs->getSizeTop()) || checkCollision(*m_player, obs->getPositionBottom(), obs->getSizeBottom())) {
					m_player->onCollisionEnter();
					setGameOver(true);
				}

				// Ako Flappy prode obstacle povecaj score
				if (!obs->isPlayerPassed() && ((obs->getPositionTop().x + obs->getSizeTop().x / 2) < m_player->getPosition().x)) {
					increaseScore();
					obs->passPlayer();
				}
			}

			createObstacles(dt);
			disposeObjects();
		}
	}

	return false;
}

bool PlayingState::render() {
	for (auto& object : m_objects)
		object.get()->render();

	renderUI();

	return false;
}

void PlayingState::increaseScore(int val) {
	m_score += val;
	m_scoreText.setString("Score: " + std::to_string(m_score));
}

void PlayingState::setGameOver(bool val) {
	m_gameOver = val;
}

bool PlayingState::isGameOver() const {
	return m_gameOver;
}

void PlayingState::setGameStarted(bool val) {
	m_gameStarted = val;
}

bool PlayingState::isGameStarted() const {
	return m_gameStarted;
}

void PlayingState::restart() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ) {
		it = m_objects.erase(it);
	}

	m_score = 0;
	m_scoreText.setString("Score: " + std::to_string(m_score));

	setGameOver(false);
	setGameStarted(false);

	m_obstacleSpawnCooldown.restart();

	createScene();
}

void PlayingState::loadResources() {
	getContext().m_textureHolder.load(ID::Textures::BACKGROUND, "Resources/Textures/background.png");
	getContext().m_textureHolder.get(ID::Textures::BACKGROUND).setRepeated(true);

	getContext().m_textureHolder.load(ID::Textures::OBSTACLE, "Resources/Textures/brick.png");
	getContext().m_textureHolder.get(ID::Textures::OBSTACLE).setRepeated(true);

	getContext().m_textureHolder.load(ID::Textures::FLAPPY, "Resources/Textures/flappy.png");

	getContext().m_fontHolder.load(ID::Fonts::ARIAL, "Resources/Fonts/arial.ttf");
}

bool PlayingState::checkCollision(Flappy& player, sf::Vector2f pos, sf::Vector2f size) {
	float playerX = player.getPosition().x + player.getCollider().getRadius();
	float playerY = player.getPosition().y + player.getCollider().getRadius();

	float leftX = pos.x;
	float rightX = leftX + size.x;

	float upY = pos.y;
	float downY = upY + size.y;

	// Pronadi tocku na pravokutniku najblizu centru player-a
	float nearestTopX = std::fmaxf(leftX, std::fminf(playerX, rightX));
	float nearestTopY = std::fmaxf(upY, std::fminf(playerY, downY));

	// Ako je centar player-a unutar pravokutnika
	// Zapravo nije potrebno jer se player nece "teleportirati" unutar pravokutnika
	if ((leftX < nearestTopX && nearestTopX < rightX) && (upY < nearestTopY && nearestTopY < downY)) {
		return true;
	}

	float deltaX = std::fabs(playerX - nearestTopX);
	float deltaY = std::fabs(playerY - nearestTopY);

	return std::powf(deltaX, 2.f) + std::powf(deltaY, 2.f) <= std::powf(player.getCollider().getRadius(), 2.f);
}

void PlayingState::createScene() {
	// Background..
	std::unique_ptr<Background> backgroundPtr(new Background(getContext(), GameObjectType::BACKGROUND));
	m_objects.push_back(std::move(backgroundPtr));

	createPlayer();
}

void PlayingState::createPlayer() {
	std::unique_ptr<Flappy> playerPtr(new Flappy(getContext(), GameObjectType::PLAYER));
	m_player = playerPtr.get();
	m_objects.push_back(std::move(playerPtr));
}

void PlayingState::disposeObjects() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ) {
		if (it->get()->isDisposed()) {
			it = m_objects.erase(it);
		}
		else {
			++it;
		}
	}
}

void PlayingState::createObstacles(sf::Time& dt) {
	if (m_obstacleSpawnCooldown.isReady(dt)) {
		std::unique_ptr<Obstacle> obstaclePtr(new Obstacle(getContext(), GameObjectType::OBSTACLE));
		m_objects.push_back(std::move(obstaclePtr));
	}
}

void PlayingState::onGameOver() {
	for (auto& object : m_objects)
		object->setPlayable(false);

	// Kad padne Flappy ispod ekrana
	if (m_player->getPosition().y > getContext().m_window.getSize().y + 50.f) {
		restart();
	}
}

void PlayingState::updateObjects(sf::Time& dt, GameObjectType type) {
	
	if (type == GameObjectType::LENGTH) {
		for (auto& object : m_objects)
			object.get()->update(dt);
	}
	else {
		for (auto& object : getObjectsByType(type))
			object->update(dt);
	}
}

void PlayingState::renderUI() {
	getContext().m_window.draw(m_scoreText);

	if (!isGameStarted()) {
		getContext().m_window.draw(m_startText);
	}
}

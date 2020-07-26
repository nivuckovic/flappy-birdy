#pragma once
#include "GameObject.h"

class Background : public GameObject {
public:
	Background(Context& context, GameObjectType type);

	void update(sf::Time& dt) override;
	void input(sf::Event& event) override;
	void render() override;

private:
	sf::Sprite m_sprite;

	sf::Vector2i m_view;
};


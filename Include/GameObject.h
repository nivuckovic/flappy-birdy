#pragma once

#include "Context.h"
#include "GameObjectType.h"

class GameObject {
public:
	GameObject(Context& context, GameObjectType type);

	virtual void update(sf::Time& dt) = 0;
	virtual void input(sf::Event &event) = 0;
	virtual void render() = 0;

	Context& getContext() const;

	void setType(GameObjectType type);
	GameObjectType getType() const;

	void setDisposed();
	bool isDisposed() const;

	bool isPlayable() const;
	void setPlayable(bool val);

	virtual void onGameOver();

private:
	Context& m_context;
	GameObjectType m_type;

	bool m_disposed;

	bool m_isPlayable;
};


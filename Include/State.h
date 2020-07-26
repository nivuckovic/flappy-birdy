#pragma once

#include "Context.h"
#include "GameObjectType.h"

#include "GameObject.h"

class State {
public:
	State(Context& context);

	virtual bool input(sf::Event& event) = 0;
	virtual bool update(sf::Time& dt) = 0;
	virtual bool render() = 0;

	virtual void loadResources() = 0;

	Context& getContext() const;

protected:
	std::vector<GameObject*> getObjectsByType(GameObjectType type);
	std::vector<std::unique_ptr<GameObject>> m_objects;

private:
	Context& m_context;

};


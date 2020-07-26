#include "State.h"
#include "..\Include\State.h"

#include "GameObject.h"

State::State(Context& context) : m_context(context) {

}

Context& State::getContext() const {
	return m_context;
}

std::vector<GameObject*> State::getObjectsByType(GameObjectType type) {
	std::vector<GameObject*> sol;

	for (auto& object : m_objects) {
		if (object.get()->getType() == type) {
			sol.push_back(object.get());
		}
	}

	return sol;
}
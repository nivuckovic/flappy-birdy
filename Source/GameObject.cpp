#include "..\Include\GameObject.h"

GameObject::GameObject(Context& context, GameObjectType type) : m_context(context), m_type(type), m_disposed(false), m_isPlayable(true) {
}

Context& GameObject::getContext() const {
	return m_context;
}

void GameObject::setType(GameObjectType type) {
	m_type = type;
}

GameObjectType GameObject::getType() const {
	return m_type;
}

void GameObject::setDisposed() {
	m_disposed = true;
}

bool GameObject::isDisposed() const {
	return false;
}

bool GameObject::isPlayable() const {
	return m_isPlayable;
}

void GameObject::setPlayable(bool val) {
	m_isPlayable = val;
}

void GameObject::onGameOver() {
	setPlayable(false);
}

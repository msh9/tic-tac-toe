#include "DraggableSprite.h"

DraggableSprite::DraggableSprite(std::unique_ptr<sf::Sprite> sprite): sprite(std::move(sprite)) { }
DraggableSprite::DraggableSprite(std::unique_ptr<sf::Sprite> sprite,
	const sf::Vector2f origin,
	const sf::Vector2f startPosition): DraggableSprite(std::move(sprite)) {
	this->sprite->setOrigin(origin);
	this->sprite->setPosition(startPosition);
}
DraggableSprite::~DraggableSprite() { }

void DraggableSprite::startDrag() {
	this->isDragging = true;
}

void DraggableSprite::endDrag() {
	this->isDragging = false;
}

const bool DraggableSprite::isDragged() const {
	return this->isDragging;
}

void DraggableSprite::setPosition(const int x, const int y) {
	if (this->isDragged()) {
		this->sprite->setPosition((float)x, (float)y);
	}
}

void DraggableSprite::setPosition(const int x, const int y, const sf::Vector2f newOrigin) {
	this->sprite->setOrigin(newOrigin);
	this->sprite->setPosition((float)x, (float)y);
}

void DraggableSprite::draw(sf::RenderWindow* window) {
	window->draw(*(this->sprite.get()));
}
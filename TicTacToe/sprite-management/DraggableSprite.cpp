#include "DraggableSprite.h"

DraggableSprite::DraggableSprite(std::unique_ptr<sf::Sprite> sprite): sprite(std::move(sprite)) { }
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

void DraggableSprite::draw(sf::RenderWindow* window) {
	window->draw(*(this->sprite.get()));
}
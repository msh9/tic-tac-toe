#pragma once
#ifndef __DRAGGABLE_SPRITE__
#define __DRAGGABLE_SPRITE__
#include <SFML/Graphics.hpp>
#include <memory>
class DraggableSprite {
public:
	DraggableSprite(const std::unique_ptr<sf::Sprite>);
	~DraggableSprite();
private:
	bool isDragging;
	std::unique_ptr<sf::Sprite> sprite;
public:
	void startDrag();
	void endDrag();
	const bool isDragged() const;
	void setPosition(const int, const int);
	void draw(sf::RenderWindow*);
};

#endif // !__DRAGGABLE_SPRITE__
#pragma once
#ifndef __DRAGGABLE_SPRITE__
#define __DRAGGABLE_SPRITE__
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
class DraggableSprite {
public:
	DraggableSprite(const std::unique_ptr<sf::Sprite>);
	DraggableSprite(const std::unique_ptr<sf::Sprite>, const sf::Vector2f, const sf::Vector2f);
	~DraggableSprite();
private:
	bool isDragging;
	std::unique_ptr<sf::Sprite> sprite;
public:
	void startDrag();
	void endDrag();
	const bool isDragged() const;
	void setPosition(const int, const int);
	void setPosition(const int, const int, const sf::Vector2f);
	void draw(sf::RenderWindow*);
};

#endif // !__DRAGGABLE_SPRITE__
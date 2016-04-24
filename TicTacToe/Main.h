#pragma once
#ifndef __Main__
#define __Main__
#include <SFML\Graphics.hpp>
#include <memory>
#include "sprite-management/DraggableSprite.h"

std::unique_ptr<DraggableSprite> handleMouseClick(const sf::Event*, const sf::Sprite*, const sf::Sprite*);
void moveDraggedSprite(const sf::Event*, DraggableSprite*);
#endif // !__Main__
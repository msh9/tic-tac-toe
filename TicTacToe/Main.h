#pragma once
#ifndef __Main__
#define __Main__
#include <SFML\Graphics.hpp>
#include <memory>
#include "sprite-management/DraggableSprite.h"

sf::Vector2f transformMouseToLocal(const sf::Event::MouseButtonEvent*, const sf::FloatRect*);
void moveDraggedSprite(const sf::Event*, DraggableSprite*);
#endif // !__Main__
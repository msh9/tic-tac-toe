#include "Main.h"
#include <memory> 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sprite-management/DraggableSprite.h"

using namespace sf;
int main() {
	sf::RenderWindow window(sf::VideoMode(1410, 910), "SFML Stuff");
	std::unique_ptr<DraggableSprite> draggedSprite = nullptr;
	/// Begin load textures
	Texture boardTexture;
	boardTexture.loadFromFile("resources/tic-tac-toe-board.png");
	Texture circleTexture;
	circleTexture.loadFromFile("resources/tic-tac-toe-circle.png");
	Texture xTexture;
	xTexture.loadFromFile("resources/tic-tac-toe-x.png");
	/// End load textures
	/// Begin create base sprites
	auto board = Sprite(boardTexture);
	auto circle = Sprite(circleTexture);
	circle.setPosition(Vector2f(950.f, 0.f));
	auto x = Sprite(xTexture);
	x.setPosition(Vector2f(950.f, 320.f));
	/// End create base sprites

	while (window.isOpen()) {
		//Base sprites are always drawn first
		window.clear();
		window.draw(board);
		window.draw(circle);
		window.draw(x);
		if (draggedSprite != nullptr) {
			draggedSprite->draw(&window);
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed: {
				window.close();
				break;
			}
			case Event::MouseButtonPressed: {
				//draggedSprite = handleMouseClick(&event, &circle, &x);
				if (event.mouseButton.button == Mouse::Left) {
					FloatRect circleBounds = circle.getGlobalBounds();
					if (circleBounds.contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
						std::cout << "Mouse clicked in circle" << std::endl;
						std::unique_ptr<Sprite> draggingCircle(new Sprite(circleTexture));
						std::unique_ptr<DraggableSprite> draggable(new DraggableSprite(std::move(draggingCircle)));
						draggable->startDrag();
						draggedSprite = std::move(draggable);
					}
					FloatRect xBounds = x.getGlobalBounds();
					if (xBounds.contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
						std::cout << "Mouse clicked in x" << std::endl;
					}
				}
				break;
			}
			case Event::MouseMoved: {
				if (draggedSprite != nullptr) {
					moveDraggedSprite(&event, draggedSprite.get());
				}
				break;
			}
			case Event::MouseButtonReleased: {
				if (draggedSprite != nullptr) {
					draggedSprite->endDrag();
				}
				break;
			}
			}
			

		}
		window.display();
	}
	return 0;
}

std::unique_ptr<DraggableSprite> handleMouseClick(const Event* event, const Sprite* circle, const Sprite* x) {
	if (event->mouseButton.button == Mouse::Left) {
		FloatRect circleBounds = circle->getGlobalBounds();
		if (circleBounds.contains((float)event->mouseButton.x, (float)event->mouseButton.y)) {
			std::cout << "Mouse clicked in circle" << std::endl;
			std::unique_ptr<Sprite> draggingCircle(new Sprite());
			std::unique_ptr<DraggableSprite> draggable(new DraggableSprite(std::move(draggingCircle)));
			return draggable;
		}
		FloatRect xBounds = x->getGlobalBounds();
		if (xBounds.contains((float)event->mouseButton.x, (float)event->mouseButton.y)) {
			std::cout << "Mouse clicked in x" << std::endl;
			return nullptr;
		}
	}
	return nullptr;
}

void moveDraggedSprite(const Event* event, DraggableSprite* draggedSprite) {
	draggedSprite->setPosition(event->mouseMove.x, event->mouseMove.y);
}
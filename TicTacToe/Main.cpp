#include "Main.h"
#include <memory> 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sprite-management/DraggableSprite.h"
#include <cmath>
#include <vector>

using namespace sf;
int main() {
	sf::RenderWindow window(sf::VideoMode(1410, 910), "Tic-Tac-Toe");
	std::unique_ptr<DraggableSprite> draggedSprite = nullptr;
	std::vector<std::unique_ptr<DraggableSprite>> placedSprite;
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
		for (auto &sprite : placedSprite) {
			sprite->draw(&window);
		}
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
						std::unique_ptr<Sprite> draggingCircle(new Sprite(circleTexture));
						std::unique_ptr<DraggableSprite> draggable(new DraggableSprite(std::move(draggingCircle), transformMouseToLocal(&event.mouseButton, &circleBounds), Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)));
						draggable->startDrag();
						draggedSprite = std::move(draggable);
					}
					FloatRect xBounds = x.getGlobalBounds();
					if (xBounds.contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
						std::unique_ptr<Sprite> draggingCircle(new Sprite(xTexture));
						std::unique_ptr<DraggableSprite> draggable(new DraggableSprite(std::move(draggingCircle), transformMouseToLocal(&event.mouseButton, &xBounds), Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)));
						draggable->startDrag();
						draggedSprite = std::move(draggable);
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
					if (event.mouseButton.x < 900.f &&
						event.mouseButton.x > 0.f &&
						event.mouseButton.y < 900.f &&
						event.mouseButton.y > 0.f) {
						auto yPosition = (int)rint(floorf((float)event.mouseButton.y / 300.f) * 300.f);
						auto xPosition = (int)rint(floorf((float)event.mouseButton.x / 300.f) * 300.f);
						draggedSprite->setPosition(xPosition, yPosition, Vector2f(0.f, 0.f));
						placedSprite.push_back(std::move(draggedSprite));
						draggedSprite = nullptr;
					} else {
						draggedSprite = nullptr;
					}
				}
				break;
			}
			}
			

		}
		window.display();
	}
	return 0;
}

sf::Vector2f transformMouseToLocal(const Event::MouseButtonEvent* mouseButton, const FloatRect* clickBounds) {
	return Vector2f(
		(float)mouseButton->x - clickBounds->left,
		(float)mouseButton->y - clickBounds->top
	);
}

void moveDraggedSprite(const Event* event, DraggableSprite* draggedSprite) {
	draggedSprite->setPosition(event->mouseMove.x, event->mouseMove.y);
}
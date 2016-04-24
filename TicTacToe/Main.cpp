#include "Main.h"
#include <memory> 
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
int main() {
	sf::RenderWindow window(sf::VideoMode(1410, 910), "SFML Stuff");

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

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed: window.close();
				break;
			case Event::MouseButtonPressed: handleMouseClick(&event, &circle, &x);
				break;
			}
		}
		window.display();
	}
	return 0;
}

void handleMouseClick(Event* event, Sprite* circle, Sprite* x) {
	if (event->mouseButton.button == Mouse::Left) {
		FloatRect circleBounds = circle->getGlobalBounds();
		if (circleBounds.contains((float)event->mouseButton.x, (float)event->mouseButton.y)) {
			std::cout << "Mouse clicked in circle" << std::endl;
		}
		FloatRect xBounds = x->getGlobalBounds();
		if (xBounds.contains((float)event->mouseButton.x, (float)event->mouseButton.y)) {
			std::cout << "Mouse clicked in x" << std::endl;
		}
	}
}

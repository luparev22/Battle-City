// Battle City.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	srand(time(NULL));
	int wx = 1280, wy = 720;
	sf::Clock clock;

	RenderWindow window(VideoMode(wx, wy), "Battle City");

	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				window.close();
			}
		}


		window.clear();
		window.display();
	}

	return 0;
}
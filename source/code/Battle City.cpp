#include "pch.h"
#include <SFML/Graphics.hpp>
#include "entity.h"
#include <list>

using namespace sf;

int main() {
	srand(time(NULL));
	int wx = 1280, wy = 720;
	sf::Clock clock;

	RenderWindow window(VideoMode(wx, wy), "Battle City");

	Image sprite;
	sprite.loadFromFile("source/img/sprites.png");

	Tank player(sprite, 640, 360, 0, 0, 16, 16);

	std::list <Entity*> entities;
	std::list <Entity*>::iterator it;

	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.setDirection('l');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.setDirection('r');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.setDirection('u');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.setDirection('d');
			player.update(dt);
		}

		for (it = entities.begin(); it != entities.end();) {
			Entity *p = *it;
			p->update(dt);
			if (!p->isAlive()) {
				it = entities.erase(it);
				delete p;
			}
		}

		window.clear();
		window.draw(*player.getSprite());
		window.display();
	}

	return 0;
}
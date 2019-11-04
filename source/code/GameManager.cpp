#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "leveling.h"
#include <fstream>
#include <string>
#include "entity.h"
#include "collision.h"
#include "GameManager.h"

using namespace sf;

void Game::StartGame() {
	int wx = 624, wy = 624;
	sf::Clock clock;
	RenderWindow window(VideoMode(wx, wy), "Battle City");

	Image icon;
	icon.loadFromFile("source/img/icon.png");
	window.setIcon(icon.getSize().y, icon.getSize().x, icon.getPixelsPtr());

	SoundBuffer buf_music;
	SoundBuffer buf_move;
	SoundBuffer buf_motor;
	SoundBuffer buf_shoot;

	buf_music.loadFromFile("source/sounds/music.wav");
	buf_move.loadFromFile("source/sounds/move.wav");
	buf_motor.loadFromFile("source/sounds/motor.wav");
	buf_shoot.loadFromFile("source/sounds/shoot.wav");
	Sound sound_once;
	Sound sound_always;
	sound_once.setVolume(50);
	sound_always.setVolume(50);

	sound_always.setBuffer(buf_motor);

	window.setFramerateLimit(20);
	Image sprite;
	sprite.loadFromFile("source/img/sprites.png");
	sprite.createMaskFromColor(sf::Color::Color(0, 0, 1), 0);

	LevelManager lm(sprite);
	lm.ReadMap(1);
	lm.DrawMap();

	std::list <Entity*> entities;
	std::list <Entity*>::iterator it;
	std::list <Entity*>::iterator it2;

	PlayerTank player(sprite, &entities, 4 * 48, 12 * 48, 0, 0, 16, 16);
	entities.push_back(&player);

	int enemies = 8;
	int enemies_on_map = 0;

	//entities.push_back(new EnemyTank(sprite, &entities, 0, 0, 0, 0, 16, 16));
	//entities.push_back(new EnemyTank(sprite, &entities, 6*48, 0, 0, 0, 16, 16));
	//entities.push_back(new EnemyTank(sprite, &entities, 12 * 48, 0, 0, 0, 16, 16));
	/*
	entities.push_back(new EnemyTank(sprite, &entities, 240, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 288, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 336, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 384, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 432, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 480, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 528, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 576, 96, 0, 0, 16, 16));
	*/

	bool isMusicOn = true;

	entities.push_back(new EnemyTank(sprite, &entities, 2 * 48, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 6 * 48, 96, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 10 * 48, 96, 0, 0, 16, 16));
	enemies_on_map += 3;

	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		Event event;
		if (sound_always.getStatus() == Sound::Status::Stopped) {
			sound_always.play();
		}
		/*
		if (enemies > 0) {
			while (enemies_on_map < 3) {
				entities.push_back(new EnemyTank(sprite, &entities, 0, 0, 0, 0, 16, 16));
				enemies_on_map++;
			}
		}
		*/


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (sound_always.getBuffer() == &buf_motor)
				sound_always.setBuffer(buf_move);
			player.setDirection('l');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (sound_always.getBuffer() == &buf_motor)
				sound_always.setBuffer(buf_move);
			player.setDirection('r');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (sound_always.getBuffer() == &buf_motor)
				sound_always.setBuffer(buf_move);
			player.setDirection('u');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (sound_always.getBuffer() == &buf_motor)
				sound_always.setBuffer(buf_move);
			player.setDirection('d');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			std::cout << player.getX() << " " << player.getY() << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player.getReload()) {
			sound_once.setBuffer(buf_shoot);
			sound_once.play();
			player.shoot(sprite);
		}



		while (window.pollEvent(event)) {
			/*
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				window.close();
			}
			*/
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
			{
				if (sound_always.getBuffer() == &buf_move)
					sound_always.setBuffer(buf_motor);
				int tile = player.getX() / 24;
				int p_x = player.getX() % 24;
				if (p_x >= 12)player.setX((tile + 1) * 24);
				else player.setX((tile) * 24);
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
			{
				if (sound_always.getBuffer() == &buf_move)
					sound_always.setBuffer(buf_motor);
				int tile = player.getX() / 24;
				int p_x = player.getX() % 24;
				if (p_x > 12)player.setX((tile + 1) * 24);
				else player.setX((tile) * 24);
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				if (sound_always.getBuffer() == &buf_move)
					sound_always.setBuffer(buf_motor);
				int tile = player.getY() / 24;
				int p_y = player.getY() % 24;
				if (p_y > 12)player.setY((tile + 1) * 24);
				else player.setY((tile) * 24);
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				if (sound_always.getBuffer() == &buf_move)
					sound_always.setBuffer(buf_motor);
				int tile = player.getY() / 24;
				int p_y = player.getY() % 24;
				if (p_y > 12)player.setY((tile + 1) * 24);
				else player.setY((tile) * 24);
			}
		}


		for (it = entities.begin(); it != entities.end();) {
			Entity* p = *it;
			if (p->getName() != "Player")
				p->update(dt);
			collisions(p, lm);
			if (!p->isAlive()) {
				if (p->getName() == "Enemy") {
					enemies_on_map--;
					enemies--;
				}
				it = entities.erase(it);
				delete p;
			}
			else {
				it++;
			}
		}




		window.clear();

		for (auto i : lm.tiles) {
			if (i->getLayout() != 1)
				window.draw(*(i->getSprite()));
		}
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw(*(*it)->getSprite());
		}
		for (auto i : lm.tiles) {
			if (i->getLayout() == 1)
				window.draw(*(i->getSprite()));
		}
		window.display();

	}


}
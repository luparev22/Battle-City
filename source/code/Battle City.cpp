#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "entity.h"
#include <list>
#include "leveling.h"
#include "collision.h"
#include <fstream>
#include "GameManager.h"
using namespace sf;





int main() {
	srand(time(NULL));
	int wx = 720, wy = 624;
	RenderWindow window(VideoMode(wx, wy), "Battle City");
	Image icon;
	icon.loadFromFile("source/img/icon.png");
	window.setIcon(icon.getSize().y, icon.getSize().x, icon.getPixelsPtr());

	Image logo;
	logo.loadFromFile("source/img/logo.png");
	
	Texture logo_texture;
	logo_texture.loadFromImage(logo);

	Sprite logo_sprite;
	logo_sprite.setTexture(logo_texture);
	logo_sprite.setPosition(0, 0);
	logo_sprite.setScale(0.4f, 0.4f);

	logo_sprite.setPosition((wx - logo_sprite.getGlobalBounds().width)/2, 50);

	//IntRect(0, 0, logo.getSize().x, logo.getSize().y)


	Font menu_font;
	menu_font.loadFromFile("source/fonts/PressStart2P.ttf");

	Image sprite;
	sprite.loadFromFile("source/img/sprites.png");
	sprite.createMaskFromColor(sf::Color::Color(0, 0, 1), 0);

	Texture texture;
	
	texture.loadFromImage(sprite);

	Text player_1;

	player_1.setFont(menu_font);
	player_1.setString("1 PLAYER");
	player_1.setPosition(300, 340);
	player_1.setCharacterSize(17);

	Text player_2;

	player_2.setFont(menu_font);
	player_2.setString("2 PLAYER");
	player_2.setPosition(player_1.getGlobalBounds().left , player_1.getGlobalBounds().top + player_1.getGlobalBounds().height+20);
	player_2.setCharacterSize(17);

	Text constructor;

	constructor.setFont(menu_font);
	constructor.setString("CONSTRUCTOR");
	constructor.setPosition(player_2.getGlobalBounds().left, player_2.getGlobalBounds().top + player_2.getGlobalBounds().height+20);
	constructor.setCharacterSize(17);

	Text exit;

	exit.setFont(menu_font);
	exit.setString("EXIT");
	exit.setPosition(constructor.getGlobalBounds().left, constructor.getGlobalBounds().top + constructor.getGlobalBounds().height + 20);
	exit.setCharacterSize(17);

	Sprite tank_pointer;
	tank_pointer.setTexture(texture);
	tank_pointer.setTextureRect(IntRect(96, 0, 16, 16));
	tank_pointer.setPosition(player_1.getGlobalBounds().left - 40, player_1.getGlobalBounds().top-8);
	tank_pointer.setScale(2, 2);

	Text all_rights;

	all_rights.setFont(menu_font);
	all_rights.setString("  (c) 2019 SibSUTIS \n ALL RIGHTS RESERVED");
	all_rights.setCharacterSize(17);
	all_rights.setPosition((wx - all_rights.getGlobalBounds().width) / 2, wy - 2*all_rights.getGlobalBounds().height);
	all_rights.setLineSpacing(2);

	std::vector <Text*> texts;
	texts.push_back(&player_1);
	texts.push_back(&player_2);
	texts.push_back(&constructor);
	texts.push_back(&exit);

	Game game;

	int currentIndex = 0;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			/*
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				window.close();
			}
			*/
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
					case Keyboard::Up:
						currentIndex--;
						if (currentIndex < 0)currentIndex = 3;
						break;
					case Keyboard::Down:
						currentIndex++;
						if (currentIndex > 3)currentIndex = 0;
						break;
					case Keyboard::Enter:
						switch (currentIndex) {
							case 0:
								game.StartGame(window);
								break;
							case 2:
								game.Constructor(window);
								break;
							case 3:
								window.close();
								break;
						}
						break;
				}
				tank_pointer.setPosition(texts[currentIndex]->getGlobalBounds().left - 40, texts[currentIndex]->getGlobalBounds().top - 8);
			}
		}



		window.clear();


		window.draw(logo_sprite);
		window.draw(tank_pointer);

		for (auto i: texts) {
			window.draw(*i);
		}
		window.draw(all_rights);
		window.display();
	}


	return 0;
}
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "entity.h"
#include <list>
#include "leveling.h"
#include "collision.h"
#include <fstream>

using namespace sf;




void game() {
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
	lm.ReadMap(999);
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

	bool isLeftPress = false;
	bool isRightPress = false;
	bool isUpPress = false;
	bool isDownPress = false;

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
			Entity *p = *it;
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


void constructor() {
	int wx = 720, wy = 624;
	sf::Clock clock;
	RenderWindow window(VideoMode(wx, wy), "Battle City");

	Image image;
	image.loadFromFile("source/img/sprites.png");
	image.createMaskFromColor(sf::Color::Color(0, 0, 1), 0);

	Texture texture;
	texture.loadFromImage(image);

	Sprite black;
	black.setTexture(texture);
	black.setTextureRect(IntRect(280, 80, 8, 8));

	Sprite brick;
	brick.setTexture(texture);
	brick.setTextureRect(IntRect(256, 64, 8, 8));

	Sprite steel;
	steel.setTexture(texture);
	steel.setTextureRect(IntRect(256, 72, 8, 8));

	Sprite water;
	water.setTexture(texture);
	water.setTextureRect(IntRect(264, 80, 8, 8));

	Sprite green;
	green.setTexture(texture);
	green.setTextureRect(IntRect(264, 72, 8, 8));

	Sprite ice;
	ice.setTexture(texture);
	ice.setTextureRect(IntRect(272, 72, 8, 8));

	Sprite state_sprite_small = black;
	state_sprite_small.setScale(3, 3);

	Sprite state_sprite = black;
	state_sprite.setTexture(texture);
	state_sprite.setScale(6, 6);
	state_sprite.setPosition(640, 20);
	state_sprite.setTextureRect(black.getTextureRect());

	Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");

	Text save;
	save.setFont(font);
	save.setString("SAVE");
	save.setPosition(650, 570);
	save.setCharacterSize(17);


	RectangleShape save_button;
	save_button.setPosition(save.getGlobalBounds().left-10, save.getGlobalBounds().top-10);
	save_button.setSize(Vector2f(save.getGlobalBounds().width+20, save.getGlobalBounds().height+20));
	save_button.setOutlineColor(Color::White);
	save_button.setFillColor(Color::Black);
	save_button.setOutlineThickness(1);
	
	int x_button = save_button.getGlobalBounds().left;
	int y_button = save_button.getGlobalBounds().top;
	int width_button = save_button.getGlobalBounds().width;
	int height_button = save_button.getGlobalBounds().height;

	char level[26][26];

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			level[i][j] = '0';
		}
	}

	std::cout << level[2][2];


	Sprite tileMap[26][26] = { black };

	std::vector <VertexArray*> grid(51);
	std::vector<VertexArray*>::iterator ptr;
	int i = 1;
	for (ptr = grid.begin(); ptr != grid.end(); i++, ptr++) {
		if (i <= 26) {
			*ptr = new VertexArray(sf::Lines, 2);
			(*(*ptr))[0].position = sf::Vector2f(i * 24, 0);
			(*(*ptr))[1].position = sf::Vector2f(i * 24, 624);
		}
		else if (i <= 51) {
			*ptr = new VertexArray(sf::Lines, 2);
			(*(*ptr))[0].position = sf::Vector2f(0, i % 26 * 24);
			(*(*ptr))[1].position = sf::Vector2f(624, i % 26 * 24);
		}
	}

	char state = '0';

	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		Event event;

		while (window.pollEvent(event)) {
			/*
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				window.close();
			}
			*/
			if (event.type == Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					state = '0';
				}
				else if (event.key.code == sf::Keyboard::Num2) {
					state = '1';
				}
				else if (event.key.code == sf::Keyboard::Num3) {
					state = '2';
				}
				else if (event.key.code == sf::Keyboard::Num4) {
					state = '3';
				}
				else if (event.key.code == sf::Keyboard::Num5) {
					state = '4';
				}
				else if (event.key.code == sf::Keyboard::Num6) {
					state = '5';
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i position = sf::Mouse::getPosition(window);
			
			if (position.x > 0 && position.x < 624 && position.y>0 && position.y < 624) {
				int x = (int)position.x / 24;
				int y = (int)position.y / 24;
				level[x][y] = state;
				tileMap[x][y] = state_sprite_small;
				tileMap[x][y].setPosition(x * 24, y * 24);
				tileMap[x][y].setScale(3, 3);
			}
			if (position.x > x_button && position.x<x_button + width_button && position.y>y_button && position.y < y_button + height_button) {
				std::ofstream out("source/map/999.txt", std::ios::out);
				if (out.is_open())
				{
					for (int i = 0; i < 26; i++) {
						for (int j = 0; j < 26; j++) {
							out << level[j][i];
							out << ' ';
						}
						out << '\n';
					}
				}
				out.close();
			}
		}

		sf::Vector2i position = sf::Mouse::getPosition(window);

		int x = save_button.getGlobalBounds().left;
		int y = save_button.getGlobalBounds().top;
		int width = save_button.getGlobalBounds().width;
		int height = save_button.getGlobalBounds().height;
		if (position.x > x_button && position.x<x_button + width_button && position.y>y_button && position.y < y_button + height_button) {
			save_button.setFillColor(Color::Red);
			save.setFillColor(Color::White);
		}
		else {
			save_button.setFillColor(Color::Black);
			save.setFillColor(Color::White);
		}

		switch (state) {
		case '0':
			state_sprite.setTextureRect(black.getTextureRect());
			state_sprite_small = black;
			break;
		case '1':
			state_sprite.setTextureRect(brick.getTextureRect());
			state_sprite_small = brick;
			break;
		case '2':
			state_sprite.setTextureRect(steel.getTextureRect());
			state_sprite_small = steel;
			break;
		case '3':
			state_sprite.setTextureRect(water.getTextureRect());
			state_sprite_small = water;
			break;
		case '4':
			state_sprite.setTextureRect(green.getTextureRect());
			state_sprite_small = green;
			break;
		case '5':
			state_sprite.setTextureRect(ice.getTextureRect());
			state_sprite_small = ice;
			break;
		}

		window.clear();

		for (ptr = grid.begin(); ptr != grid.end(); ptr++) {
			window.draw(*(*ptr));
		}
		
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				window.draw(tileMap[i][j]);
			}
		}
		window.draw(save_button);
		window.draw(save);
		window.draw(state_sprite);
		window.display();

	}


}




int main() {
	srand(time(NULL));

	char choice;
	std::cin >> choice;

	if (choice == '1') {
		game();
	}
	else if (choice == '2') {
		constructor();
	}

	return 0;
}
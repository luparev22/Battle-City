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

void DrawSideBar(Image sprite , Font stageFont,int health,int level, RenderWindow& window) {
	Texture texture;
	texture.loadFromImage(sprite);

	Sprite firstPlayerSprite;
	firstPlayerSprite.setTexture(texture);
	firstPlayerSprite.setTextureRect(IntRect(376, 136, 16, 8));
	firstPlayerSprite.setPosition(648, 336);
	firstPlayerSprite.setScale(3, 3);

	Sprite firstPlayerTankSprite;
	firstPlayerTankSprite.setTexture(texture);
	firstPlayerTankSprite.setTextureRect(IntRect(376, 144, 8, 8));
	firstPlayerTankSprite.setPosition(648, 360);
	firstPlayerTankSprite.setScale(3, 3);

	Text Life;
	Life.setFont(stageFont);
	Life.setString(std::to_string(health));
	Life.setCharacterSize(20);
	Life.setPosition(678, 364);
	Life.setFillColor(Color(0, 0, 1));

	Sprite Flag;
	Flag.setTexture(texture);
	Flag.setTextureRect(IntRect(376, 184, 16, 16));
	Flag.setPosition(648, 480);
	Flag.setScale(3, 3);

	Text FlagText;
	FlagText.setFont(stageFont);
	FlagText.setString(std::to_string(level));
	FlagText.setCharacterSize(20);
	FlagText.setPosition(658, 528);
	FlagText.setFillColor(Color(0, 0, 1));

	RectangleShape sideBar;
	sideBar.setFillColor(Color(99, 99, 99));
	sideBar.setPosition(624, 0);
	sideBar.setSize(Vector2f(96, 624));

	window.draw(sideBar);
	window.draw(firstPlayerTankSprite);
	window.draw(firstPlayerSprite);
	window.draw(Life);
	window.draw(Flag);
	window.draw(FlagText);
}

void Game::StartGame(RenderWindow &window,int level) {
	sf::Clock clock;
	int wx = 720, wy = 624;
	int stage = 1;
	Font stageFont;
	stageFont.loadFromFile("source/fonts/PressStart2P.ttf");

	Text stageText;
	stageText.setFont(stageFont);
	stageText.setString("STAGE " + std::to_string(stage));
	stageText.setCharacterSize(17);
	stageText.setPosition((wx - stageText.getGlobalBounds().width) / 2, (wy - stageText.getGlobalBounds().height)/2);

	window.clear(Color(99, 99, 99));
	window.draw(stageText);
	window.display();

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
	lm.ReadMap(level);
	lm.DrawMap();

	std::list <Entity*> entities;
	std::list <Entity*>::iterator it;
	std::list <Entity*>::iterator it2;

	PlayerTank player(sprite, &entities, 4 * 48, 12 * 48, 0, 0, 16, 16);
	entities.push_back(&player);

	int enemies = 20;
	int enemies_on_map = 0;

	std::list<Sprite> enemesSprite;
	Texture texture;
	texture.loadFromImage(sprite);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			Sprite spriteMiniTank;
			spriteMiniTank.setTexture(texture);
			spriteMiniTank.setTextureRect(IntRect(320, 192, 8, 8));
			spriteMiniTank.setPosition(648 + 24 * j, 24 + 24 * i);
			spriteMiniTank.setScale(3, 3);
			enemesSprite.push_back(spriteMiniTank);
		}
	}

	std::vector<EnemyTank> enemes;
	
	bool isMusicOn = true;
	
	bool spawnPoint1 = true, spawnPoint2 = true, spawnPoint3 = true;
	
	Sprite anim[4];
	for (int i = 0; i < 4; i++) {
		anim[i].setTexture(texture);
		anim[i].setTextureRect(IntRect(256+16*i, 96, 16 , 16));
		anim[i].setPosition(0,0);
		anim[i].setScale(3, 3);
	}
	int curInd=0,times=0,prevSpawn=-1;
	bool nowSpawning = false;

	while (window.isOpen()) {
		if (times > 2) {
			nowSpawning = false;
			times = 0;
			curInd = 0;
			entities.push_back(new EnemyTank(sprite, &entities, anim[0].getPosition().x, anim[0].getPosition().y, 0, 0, 16, 16));
			enemies_on_map += 1;
			if(!enemesSprite.empty())
			enemesSprite.pop_back();
		}

		if (enemies_on_map < 4&& !enemesSprite.empty()) {
			if (!nowSpawning) {
				int r = rand() % 3;
				if (r != prevSpawn) {
					switch (r)
					{
					case 0:
						for (int i = 0; i < 4; i++) {
							anim[i].setPosition(0, 0);
						}
						break;
					case 1:
						for (int i = 0; i < 4; i++) {
							anim[i].setPosition(48 * 6, 0);
						}
						break;
					case 2:
						for (int i = 0; i < 4; i++) {
							anim[i].setPosition(48 * 12, 0);
						}
						break;
					}
					prevSpawn = r;
					nowSpawning = true;
				}
			}
			else {
				curInd++;
				if (curInd >= 11) {
					times++;
					curInd = 0;
				}
			}
		}

		float dt = clock.restart().asSeconds();
		Event event;
		if (sound_always.getStatus() == Sound::Status::Stopped) {
			sound_always.play();
		}


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

		DrawSideBar(sprite, stageFont, health, level, window);
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
		if (nowSpawning)
			window.draw(anim[curInd / 3]);
		for (auto i : enemesSprite) {
			window.draw(i);
		}
		window.display();

	}


}

void Game::Constructor(RenderWindow &window) {
	sf::Clock clock;

	Image image;
	image.loadFromFile("source/img/sprites.png");
	image.createMaskFromColor(sf::Color::Color(0, 0, 1), 0);

	Texture texture;
	texture.loadFromImage(image);

	Sprite base_a;
	base_a.setTexture(texture);
	base_a.setTextureRect(IntRect(304, 32, 8, 8));

	Sprite base_b;
	base_b.setTexture(texture);
	base_b.setTextureRect(IntRect(312, 32, 8, 8));

	Sprite base_c;
	base_c.setTexture(texture);
	base_c.setTextureRect(IntRect(304, 40, 8, 8));

	Sprite base_d;
	base_d.setTexture(texture);
	base_d.setTextureRect(IntRect(312, 40, 8, 8));



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
	save.setPosition(650, 520);
	save.setCharacterSize(17);

	Text back;
	back.setFont(font);
	back.setString("BACK");
	back.setPosition(650, 570);
	back.setCharacterSize(17);


	RectangleShape save_button;
	save_button.setPosition(save.getGlobalBounds().left - 10, save.getGlobalBounds().top - 10);
	save_button.setSize(Vector2f(save.getGlobalBounds().width + 20, save.getGlobalBounds().height + 20));
	save_button.setOutlineColor(Color::White);
	save_button.setFillColor(Color::Black);
	save_button.setOutlineThickness(1);

	int x_button_save = save_button.getGlobalBounds().left;
	int y_button_save = save_button.getGlobalBounds().top;
	int width_button_save = save_button.getGlobalBounds().width;
	int height_button_save = save_button.getGlobalBounds().height;

	RectangleShape back_button;
	back_button.setPosition(back.getGlobalBounds().left - 10, back.getGlobalBounds().top - 10);
	back_button.setSize(Vector2f(back.getGlobalBounds().width + 20, back.getGlobalBounds().height + 20));
	back_button.setOutlineColor(Color::White);
	back_button.setFillColor(Color::Black);
	back_button.setOutlineThickness(1);

	int x_button_back  = back_button.getGlobalBounds().left;
	int y_button_back = back_button.getGlobalBounds().top;
	int width_button_back = back_button.getGlobalBounds().width;
	int height_button_back = back_button.getGlobalBounds().height;

	RectangleShape block_highlight;
	block_highlight.setPosition(state_sprite.getGlobalBounds().left, state_sprite.getGlobalBounds().top);
	block_highlight.setSize(Vector2f(48, 48));
	block_highlight.setOutlineColor(Color::White);
	block_highlight.setFillColor(Color::Black);
	block_highlight.setOutlineThickness(2);

	Text text_highlight;
	text_highlight.setFont(font);
	text_highlight.setString("BLOCK");
	text_highlight.setPosition(block_highlight.getGlobalBounds().left, block_highlight.getGlobalBounds().top+block_highlight.getGlobalBounds().height);
	text_highlight.setCharacterSize(17);

	char level[26][26];

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			level[i][j] = '0';
		}
	}
	//////////////////////////////////
	level[11][25] = '1';
	level[11][24] = '1';
	level[11][23] = '1';
	level[12][23] = '1';
	level[13][23] = '1';
	level[14][23] = '1';
	level[14][24] = '1';
	level[14][25] = '1';
	level[12][24] = 'a';
	level[13][24] = 'b';
	level[12][25] = 'c';
	level[13][25] = 'd';
	/////////////////////////////////

	Sprite tileMap[26][26] = { black };

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			switch (level[i][j]) {
				case '0':
					tileMap[i][j] = black;
					break;
				case '1':
					tileMap[i][j] = brick;
					break;
				case '2':
					tileMap[i][j] = steel;
					break;
				case '3':
					tileMap[i][j] = water;
					break;
				case '4':
					tileMap[i][j] = green;
					break;
				case '5':
					tileMap[i][j] = ice;
					break;
				case 'a':
					tileMap[i][j] = base_a;
					break;
				case 'b':
					tileMap[i][j] = base_b;
					break;
				case 'c':
					tileMap[i][j] = base_c;
					break;
				case 'd':
					tileMap[i][j] = base_d;
					break;
			}
			tileMap[i][j].setPosition(i * 24, j * 24);
			tileMap[i][j].setScale(3, 3);

		}
	}


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

			if (position.x > 0 && position.x < 624 && position.y>0 && position.y < 624 ) {
				if ((position.x > 11 * 24-1 && position.y > 23 * 24-1 && position.x < 15 * 24+1) || (position.x > 0 * 24 - 1 && position.y < 2 * 24 + 1 && position.x < 2 * 24 + 1) 
					|| (position.x > 12 * 24 - 1 && position.y < 2 * 24 + 1 && position.x < 14 * 24 + 1) || (position.x > 24 * 24 - 1 && position.y < 2 * 24 + 1 && position.x < 26 * 24 + 1) 
					|| (position.x > 8 * 24 - 1 && position.y > 24 * 24 - 1 && position.x < 10 * 24 + 1) || (position.x > 16 * 24 - 1 && position.y > 24 * 24 - 1 && position.x < 18 * 24 + 1)) {

				}
				else {
					int x = (int)position.x / 24;
					int y = (int)position.y / 24;
					level[x][y] = state;
					tileMap[x][y] = state_sprite_small;
					tileMap[x][y].setPosition(x * 24, y * 24);
					tileMap[x][y].setScale(3, 3);
				}
			}
			if (position.x > x_button_save && position.x<x_button_save + width_button_save && position.y>y_button_save && position.y < y_button_save + height_button_save) {
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
				return;
			}
			if (position.x > x_button_back && position.x<x_button_back + width_button_back && position.y>y_button_back && position.y < y_button_back + height_button_back) {
				return;
			}
		}

		sf::Vector2i position = sf::Mouse::getPosition(window);

		if (position.x > x_button_save && position.x<x_button_save + width_button_save && position.y>y_button_save && position.y < y_button_save + height_button_save) {
			save_button.setFillColor(Color::Red);
			save.setFillColor(Color::White);
		}
		else {
			save_button.setFillColor(Color::Black);
			save.setFillColor(Color::White);
		}

		if (position.x > x_button_back && position.x<x_button_back + width_button_back && position.y>y_button_back && position.y < y_button_back + height_button_back) {
			back_button.setFillColor(Color::Red);
			back.setFillColor(Color::White);
		}
		else {
			back_button.setFillColor(Color::Black);
			back.setFillColor(Color::White);
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
		window.draw(back_button);
		window.draw(back);
		window.draw(block_highlight);
		window.draw(text_highlight);
		window.draw(state_sprite);
		window.display();

	}

}
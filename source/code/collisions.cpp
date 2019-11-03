#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp> 
#include "leveling.h"
#include <fstream>
#include <string>
#include "entity.h"
#include "collision.h"

using namespace sf;


void collisions(Entity* player,LevelManager lm) {
	int x = player->getX();
	int y = player->getY();
	x /= 48;
	y /= 48;
	if (!lm.tiles[13 * y + x]->getDrive()) {
		if (player->getY() - lm.tiles[13 * y + x]->getY() > 24 && player->getDirection() == 'u') {
			player->setY(lm.tiles[13 * y + x]->getY() + 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (player->getX() - lm.tiles[13 * y + x]->getX() > 24 && player->getDirection() == 'l') {
			player->setX(lm.tiles[13 * y + x]->getX() + 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
	if (x < 12 && !lm.tiles[13 * y + x + 1]->getDrive()) {
		if (player->getY() - lm.tiles[13 * y + x + 1]->getY() > 24
			&& lm.tiles[13 * y + x + 1]->getX() - player->getX() != 48 && player->getDirection() == 'u') {
			player->setY(lm.tiles[13 * y + x]->getY() + 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (lm.tiles[13 * y + x + 1]->getX() - player->getX() > 24 && player->getDirection() == 'r') {
			player->setX(lm.tiles[13 * y + x + 1]->getX() - 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
	if (y < 12 && !lm.tiles[13 * (y + 1) + x]->getDrive()) {
		if (lm.tiles[13 * (y + 1) + x]->getY() - player->getY() > 24 && player->getDirection() == 'd') {
			player->setY(lm.tiles[13 * (y + 1) + x]->getY() - 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (player->getX() - lm.tiles[13 * (y + 1) + x]->getX() > 24
			&& lm.tiles[13 * (y + 1) + x]->getY() - player->getY() != 48 && player->getDirection() == 'l') {
			player->setX(lm.tiles[13 * (y + 1) + x]->getX() + 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
	if (y < 12 && x < 12 && !lm.tiles[13 * (y + 1) + x + 1]->getDrive()) {
		if (lm.tiles[13 * (y + 1) + x + 1]->getY() - player->getY() > 24
			&& lm.tiles[13 * (y + 1) + x + 1]->getX() - player->getX() != 48 && player->getDirection() == 'd') {
			player->setY(lm.tiles[13 * (y + 1) + x + 1]->getY() - 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (lm.tiles[13 * (y + 1) + x + 1]->getX() - player->getX() > 24
			&& lm.tiles[13 * (y + 1) + x + 1]->getY() - player->getY() != 48 && player->getDirection() == 'r') {
			player->setX(lm.tiles[13 * y + x + 1]->getX() - 48);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
}
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "leveling.h"
#include <fstream>
#include <string>
#include "entity.h"
#include "collision.h"

using namespace sf;

int globalDel = 24;

void collisions(Entity* player,LevelManager lm) {
	int x = player->getX();
	int y = player->getY();
	x /= globalDel;
	y /= globalDel;
	if (player->getName() == "Bullet") {
		if (player->getDirection() == 'u' && x < 25) {
			std::cout << lm.tiles[26 * y + x]->getDrive() << lm.tiles[26 * y + x + 1]->getDrive() << std::endl;
			if (!lm.tiles[26 * y + x]->getDrive() || !lm.tiles[26 * y + x + 1]->getDrive()) {
				if (lm.tiles[26 * y + x]->getBreak()) {
					lm.tiles[26 * y + x]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * y + x]->setBreak(false);
					lm.tiles[26 * y + x]->setDrive(true);
				}
				if (lm.tiles[26 * y + x + 1]->getBreak()) {
					lm.tiles[26 * y + x + 1]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * y + x + 1]->setBreak(false);
					lm.tiles[26 * y + x + 1]->setDrive(true);
				}
				player->setAlive(false);
				((Bullet*)player)->getFather()->setReload(false);
			}
		}
		if (player->getDirection() == 'd' && y < 25 && x < 25) {
			if (!lm.tiles[26 * (y + 1) + x]->getDrive() || !lm.tiles[26 * (y + 1) + x + 1]->getDrive()) {
				if (lm.tiles[26 * (y + 1) + x]->getBreak()) {
					lm.tiles[26 * (y + 1) + x]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * (y + 1) + x]->setBreak(false);
					lm.tiles[26 * (y + 1) + x]->setDrive(true);
				}
				if (lm.tiles[26 * (y + 1) + x + 1]->getBreak()) {
					lm.tiles[26 * (y + 1) + x + 1]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * (y + 1) + x + 1]->setBreak(false);
					lm.tiles[26 * (y + 1) + x + 1]->setDrive(true);
				}
				player->setAlive(false);
				((Bullet*)player)->getFather()->setReload(false);
			}
		}
		if (player->getDirection() == 'r' && y < 25 && x < 25) {
			if (!lm.tiles[26 * y + x + 1]->getDrive() || !lm.tiles[26 * (y + 1) + x + 1]->getDrive()) {
				if (lm.tiles[26 * y + x + 1]->getBreak()) {
					lm.tiles[26 * y + x + 1]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * y + x + 1]->setBreak(false);
					lm.tiles[26 * y + x + 1]->setDrive(true);
				}
				if (lm.tiles[26 * (y + 1) + x + 1]->getBreak()) {
					lm.tiles[26 * (y + 1) + x + 1]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * (y + 1) + x + 1]->setBreak(false);
					lm.tiles[26 * (y + 1) + x + 1]->setDrive(true);
				}
				player->setAlive(false);
				((Bullet*)player)->getFather()->setReload(false);
			}
		}
		if (player->getDirection() == 'l' && y < 25) {
			if (!lm.tiles[26 * y + x]->getDrive() || !lm.tiles[26 * (y + 1) + x]->getDrive()) {
				if (lm.tiles[26 * y + x]->getBreak()) {
					lm.tiles[26 * y + x]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * y + x]->setBreak(false);
					lm.tiles[26 * y + x]->setDrive(true);
				}
				if (lm.tiles[26 * (y + 1) + x]->getBreak()) {
					lm.tiles[26 * (y + 1) + x]->setSprite(*lm.tiles[0]->getSprite());
					lm.tiles[26 * (y + 1) + x]->setBreak(false);
					lm.tiles[26 * (y + 1) + x]->setDrive(true);
				}
				player->setAlive(false);
				((Bullet*)player)->getFather()->setReload(false);
			}
		}
	}
	else {
		if (player->getDirection() == 'u' && x < 25) {
			if (!lm.tiles[26 * y + x]->getDrive() || !lm.tiles[26 * y + x + 1]->getDrive()) {
				player->setY(lm.tiles[26 * y + x]->getY() + globalDel);
				player->getSprite()->setPosition(player->getX(), player->getY());
			}
		}
		if (player->getDirection() == 'd' && y < 24 && x < 25) {
			if (!lm.tiles[26 * (y + 2) + x]->getDrive() || !lm.tiles[26 * (y + 2) + x + 1]->getDrive()) {
				player->setY(lm.tiles[26 * (y + 2) + x]->getY() - 2 * globalDel);
				player->getSprite()->setPosition(player->getX(), player->getY());
			}
		}
		if (player->getDirection() == 'r' && y < 25 && x < 24) {
			if (!lm.tiles[26 * y + x + 2]->getDrive() || !lm.tiles[26 * (y + 1) + x + 2]->getDrive()) {
				player->setX(lm.tiles[26 * y + x + 2]->getX() - 2 * globalDel);
				player->getSprite()->setPosition(player->getX(), player->getY());
			}
		}
		if (player->getDirection() == 'l' && y < 25) {
			if (!lm.tiles[26 * y + x]->getDrive() || !lm.tiles[26 * (y + 1) + x]->getDrive()) {
				player->setX(lm.tiles[26 * y + x]->getX() + globalDel);
				player->getSprite()->setPosition(player->getX(), player->getY());
			}
		}
	}
	/*
	if (!lm.tiles[13 * y + x]->getDrive()) {
		if (player->getY() - lm.tiles[13 * y + x]->getY() > globalDel/2 && player->getDirection() == 'u') {
			player->setY(lm.tiles[13 * y + x]->getY() + globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (player->getX() - lm.tiles[13 * y + x]->getX() > globalDel/2 && player->getDirection() == 'l') {
			player->setX(lm.tiles[13 * y + x]->getX() + globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
	if (x < 12 && !lm.tiles[13 * y + x + 1]->getDrive()) {
		if (player->getY() - lm.tiles[13 * y + x + 1]->getY() > globalDel/2
			&& lm.tiles[13 * y + x + 1]->getX() - player->getX() != globalDel && player->getDirection() == 'u') {
			player->setY(lm.tiles[13 * y + x]->getY() + globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (lm.tiles[13 * y + x + 1]->getX() - player->getX() > globalDel/2 && player->getDirection() == 'r') {
			player->setX(lm.tiles[13 * y + x + 1]->getX() - globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
	if (y < 12 && !lm.tiles[13 * (y + 1) + x]->getDrive()) {
		if (lm.tiles[13 * (y + 1) + x]->getY() - player->getY() > globalDel/2 && player->getDirection() == 'd') {
			player->setY(lm.tiles[13 * (y + 1) + x]->getY() - globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
		if (player->getX() - lm.tiles[13 * (y + 1) + x]->getX() > globalDel/2
			&& lm.tiles[13 * (y + 1) + x]->getY() - player->getY() != globalDel && player->getDirection() == 'l') {
			player->setX(lm.tiles[13 * (y + 1) + x]->getX() + globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
		}
	}
	if (y < 12 && x < 12 && !lm.tiles[13 * (y + 1) + x + 1]->getDrive()) {
		if (lm.tiles[13 * (y + 1) + x + 1]->getY() - player->getY() > globalDel/2
			&& lm.tiles[13 * (y + 1) + x + 1]->getX() - player->getX() != globalDel && player->getDirection() == 'd') {
			player->setY(lm.tiles[13 * (y + 1) + x + 1]->getY() - globalDel);
			player->getSprite()->setPosition(player->getX(), player->getY());
>>>>>>> 71dc5b37ee96774aa02523217c351d2940a64eaa
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
	*/
}
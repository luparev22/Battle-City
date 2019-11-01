#pragma once
#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace sf;

class Entity {
private:
	Texture texture;
	Sprite sprite;
	String name;
	float x;
	float y;
	int W;
	int H;
	bool alive;
	std::list <Entity*> *entities;
public:
	Entity(Image image, std::list <Entity*> *entities, float x, float y, int x_image, int y_image, int W, int H);
	Sprite* getSprite() { return &sprite; };
	float getX() { return x; };
	float getY() { return y; };
	void setX(float new_x) { x = new_x; };
	void setY(float new_y) { y = new_y; };
	virtual void update(float dt) = 0;
	bool isAlive() { return alive; };
	void setAlive(bool al) { alive = al; };
	FloatRect getRect() {
		return FloatRect((float)x+16, (float)y+16, (float)W*3, (float)H*3);
	}
	std::list <Entity*>* getEntities() { return entities; };
	void setName(String str) {
		name = str;
	}
	Texture getTexture() {
		return texture;
	};
	String getName() { return name; };
};

class Tank : public Entity {
	private:
		float speed;
		unsigned short int tankLevel;
		char direction;
		bool anim = true;
		bool reload = false;
	public:
		Tank(Image image, std::list <Entity*> *entities, float x, float y, int x_image, int y_image, int W, int H);
		void update(float dt)=0;
		void setDirection(char dir) { direction = dir; };
		void shoot(Image image);
		void setReload(bool rel) { reload = rel; };
		void setAnim(bool an) { anim = an; };
		void setSpeed(float spd) { speed = spd; };
		void setTankLevel(int tl) { tankLevel = tl; };
		unsigned short int getTankLevel() { return tankLevel; };
		char getDirection() { return direction; };
		bool getReload() { return reload; };
		bool getAnim() { return anim; };
		float getSpeed() { return speed; };
};

class PlayerTank : public Tank {
	public:
		PlayerTank(Image image, std::list <Entity*> *entities, float x, float y, int x_image, int y_image, int W, int H);
		void update(float dt);
};

class EnemyTank : public Tank {
	private:
		bool isBonusTank;
	public:
		EnemyTank(Image image, std::list <Entity*> *entities, float x, float y, int x_image, int y_image, int W, int H);
		void changeDirection();
		void update(float dt);
};

class Bullet :public Entity {
private:
	float speed;
	char direction;
	Tank* father;
public:
	Bullet(Tank *player, Image image, std::list <Entity*> *entities, float x, float y, int x_image, int y_image, int W, int H);
	void update(float dt);
	Tank* getFather() { return father; };
};
#endif
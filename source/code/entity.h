#pragma once
#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Entity {
private:
	Texture texture;
	Sprite sprite;
	float x;
	float y;
	bool alive;
public:
	Entity(Image image, float x, float y, int x_image, int y_image, int W, int H);
	Sprite* getSprite() { return &sprite; };
	float getX() { return x; };
	float getY() { return y; };
	void setX(float new_x) { x = new_x; };
	void setY(float new_y) { y = new_y; };
	virtual void update(float dt) = 0;
	bool isAlive() { return alive; };
	void setAlive(bool al) { alive = al; };
};

class Tank : public Entity {
private:
	float speed;
	unsigned short int tankLevel;
	char direction;
	bool anim = true;
public:
	Tank(Image image, float x, float y, int x_image, int y_image, int W, int H);
	void Shoot();
	void LevelUp();
	void update(float dt);
	void setDirection(char dir) { direction = dir; };
	char getDirection() { return direction; };
};

#endif
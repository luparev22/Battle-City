#pragma once
#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "animations.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Boom {
	private:
		Image img;
		Texture texture;
		Sprite sprite;
		bool remove = false;
		int x;
		int y;
	public:
		int iterator;
		Boom(int x,int y);
		virtual void update() = 0;
		bool getRemove() { return remove; };
		void setRemove(bool rem) { remove = rem; };
		Sprite* getSprite() { return &sprite; };
		int getX() { return x; };
		int getY() { return y; };
};

class BoomTank:public Boom {
public:
	BoomTank(int x, int y);
	void update();
};

class BoomBullet:public Boom {
public:
	BoomBullet(int x, int y);
	void update();
};


#endif
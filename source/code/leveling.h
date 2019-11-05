#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
using namespace sf;

class Tile;

class LevelManager {
private:
	char currentMap[26][26];
	Image image;
public:
	std::vector<Tile*> tiles;
	LevelManager(Image img) {
		image = img;
	}
	void ReadMap(int n);
	void DrawMap();
	Image getImage() { return image; };
};

class Tile {
private:
	Texture texture;
	Sprite sprite;
	int x;
	int y;
	bool isBreakable;
	bool isDriveable;
	int layout;
public:
	int getX() { return x; };
	int getY() { return y; };
	bool getDrive() { return isDriveable; };
	bool getBreak() { return isBreakable; };
	IntRect getRect() { return IntRect(x, y, 48, 48); };
	int getLayout() { return layout; };
	Sprite* getSprite() { return &sprite; };
	void setBreak(bool isBreak) { isBreakable = isBreak; };
	void setSprite(Sprite& newsprite) { sprite = newsprite; };
	void setDrive(bool isDrive) { isDriveable = isDrive; };
	void setSprite(Image img, int x_image, int y_image, int W, int H,bool breakable) {
		texture.loadFromImage(img);
		isBreakable = breakable;
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x_image, y_image, W, H));
		sprite.setPosition(x, y);
		sprite.setScale(3, 3);
	};
	Tile(Image img, int x, int y, int x_image, int y_image, int W, int H,bool breakable,bool drive,int layout)
	: x(x), y(y),isBreakable(breakable),isDriveable(drive),layout(layout)
	{
		texture.loadFromImage(img);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x_image, y_image, W, H));
		sprite.setPosition(x, y);
		sprite.setScale(3, 3);
	}
	
};

#endif
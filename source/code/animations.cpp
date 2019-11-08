#include "pch.h"
#include "animations.h"

Boom::Boom(int x,int y) {
	iterator = 1;
	img.loadFromFile("source/img/sprites.png");
	img.createMaskFromColor(sf::Color::Color(0, 0, 1), 0);
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(256, 128, 16, 16));
	this->x = x;
	this->y = y;
	sprite.scale(3, 3);
}

void BoomTank::update() {
	iterator++;
	if (iterator > 9) {
		setRemove(true);
	}
	switch (iterator / 2) {
	case 0: getSprite()->setTextureRect(IntRect(256, 128, 16, 16));
		break;
	case 1: getSprite()->setTextureRect(IntRect(256 + 1 * 16, 128, 16, 16));
		break;
	case 2: getSprite()->setTextureRect(IntRect(256 + 2 * 16, 128, 16, 16));
		break;
	case 3: getSprite()->setTextureRect(IntRect(304, 128, 32, 32));
		break;
	case 4: getSprite()->setTextureRect(IntRect(304 + 1 * 32, 128, 32, 32));
		break;
	}
	getSprite()->setOrigin(getSprite()->getLocalBounds().width / 2, getSprite()->getLocalBounds().height / 2);
	getSprite()->setPosition(getX(), getY());
}

BoomTank::BoomTank(int x, int y):Boom(x,y){
}

void BoomBullet::update() {
	iterator++;
	if (iterator > 3) {
		setRemove(true);
	}
	switch (iterator / 2) {
	case 0: getSprite()->setTextureRect(IntRect(256, 128, 16, 16));
		break;
	case 1: getSprite()->setTextureRect(IntRect(256 + 1 * 16, 128, 16, 16));
		break;
	}
	getSprite()->setOrigin(getSprite()->getLocalBounds().width / 2, getSprite()->getLocalBounds().height / 2);
	getSprite()->setPosition(getX(), getY());
}

BoomBullet::BoomBullet(int x, int y):Boom(x, y) {
}
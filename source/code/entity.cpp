#include "pch.h"
#include "entity.h"

Entity::Entity(Image image, float x, float y, int x_image, int y_image, int W, int H) :x(x), y(y), alive(true) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x_image, y_image, W, H));
	sprite.setPosition(x, y);
}

Tank::Tank(Image image, float x, float y, int x_image, int y_image, int W, int H) :Entity(image, x, y, x_image, y_image, W, H), speed(500), direction('u'), tankLevel(3) {
	
	getSprite()->setScale(3, 3);
}

void Tank::update(float dt) {
	switch (getDirection()) {
	case 'u':
		direction = 'u';
		if (anim) {
			getSprite()->setTextureRect(IntRect(0, 16 * tankLevel, 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(16, 16 * tankLevel, 16, 16));
		}
		anim = !anim;
		setY(getY() - dt * speed);
		break;
	case 'd':
		direction = 'd';
		if (anim) {
			getSprite()->setTextureRect(IntRect(64, 16 * tankLevel, 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(80, 16 * tankLevel, 16, 16));

		}
		anim = !anim;
		setY(getY() + dt * speed);
		break;
	case 'l':
		direction = 'l';
		if (anim) {
			getSprite()->setTextureRect(IntRect(32, 16 * tankLevel, 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(48, 16 * tankLevel, 16, 16));
		}
		anim = !anim;
		setX(getX() - dt * speed);
		break;
	case 'r':
		direction = 'r';
		if (anim) {
			getSprite()->setTextureRect(IntRect(96, 16 * tankLevel, 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(112, 16 * tankLevel, 16, 16));

		}
		anim = !anim;
		setX(getX() + dt * speed);
		break;
	}
	getSprite()->setPosition(getX(), getY());
}
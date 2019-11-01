#include "pch.h"
#include "entity.h"

Entity::Entity(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) :entities(entities),x(x), y(y),W(W),H(H), alive(true) {

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x_image, y_image, W, H));
	sprite.setPosition(x, y);
	getSprite()->setScale(3, 3);

}

Tank::Tank(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) :Entity(image,entities, x, y, x_image, y_image, W, H), speed(4), direction('u'), tankLevel(3) {}

void Tank::shoot(Image image) {
	getEntities()->push_back(new Bullet(this, image, getEntities(), 0, 0, 323, 102, 3, 4));
}

PlayerTank::PlayerTank(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) : Tank(image,entities, x, y, x_image, y_image, W, H) {
	setName("Player");
	getSprite()->setTextureRect(IntRect(0, 16 * getTankLevel(), 16, 16));
};

EnemyTank::EnemyTank(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) : Tank(image,entities, x, y, x_image, y_image, W, H) {
	setName("Enemy");
	getSprite()->setTextureRect(IntRect(128, 16 * getTankLevel(), 16, 16));
};

Bullet::Bullet(Tank *player, Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) :Entity(image, entities, x, y, x_image, y_image, W, H) {
	setName("Bullet");
	player->setReload(true);
	direction = player->getDirection();
	setX(player->getX()+16);
	setY(player->getY()+16);
	setAlive(true);
	speed = 16;
	father = player;
	switch (direction) {
		case 'u':
			getSprite()->setTextureRect(IntRect(323, 102, 3, 4));
			break;
		case 'd':
			getSprite()->setTextureRect(IntRect(339, 102, 3, 4));
			break;
		case 'l':
			getSprite()->setTextureRect(IntRect(330, 102, 4, 3));
			break;
		case 'r':
			getSprite()->setTextureRect(IntRect(346, 102, 4, 3));
			break;
	}

}

void Bullet::update(float dt) {
		switch (direction) {
		case 'u':
			setY(getY() - speed);
			break;
		case 'd':
			setY(getY() + speed);
			break;
		case 'l':
			setX(getX() - speed);
			break;
		case 'r':
			setX(getX() + speed);
			break;
		}
		if (getX() > 624 || getX() < 0 || getY() < 0-12 || getY() > 624+12) {
			setAlive(false);
			getFather()->setReload(false);
		}
		std::list <Entity*> entities = *getEntities();
		std::list <Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); it++) {
			if (father->getName() == "Player") {
				if ((*it) == this)continue;
				if ((*it) == father)continue;
				if (this->getRect().intersects((*it)->getRect())) {
					(*it)->setAlive(false);
					this->setAlive(false);
					getFather()->setReload(false);
				}
			}
			else if (father->getName() == "Enemy") {
				if ((*it) == this)continue;
				if ((*it)->getName()=="Enemy")continue;
				if (this->getRect().intersects((*it)->getRect())) {
					(*it)->setAlive(false);
					this->setAlive(false);
					getFather()->setReload(false);
				}
			}else if ((*it)->getName() == "Bullet") {
				if ((*it) == this)continue;
				if (this->getRect().intersects((*it)->getRect())) {
					(*it)->setAlive(false);
					this->setAlive(false);
					getFather()->setReload(false);
				}
			}

		}
		getSprite()->setPosition(getX(), getY());
}

void PlayerTank::update(float dt) {
	switch (getDirection()) {
	case 'u':
		setDirection('u');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(0, 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(16, 16 * getTankLevel(), 16, 16));
		}
		setAnim(!getAnim());

		setY(getY() - getSpeed());

		break;
	case 'd':
		setDirection('d');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(64, 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(80, 16 * getTankLevel(), 16, 16));

		}
		setAnim(!getAnim());

		setY(getY() + getSpeed());

		break;
	case 'l':
		setDirection('l');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(32, 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(48, 16 * getTankLevel(), 16, 16));
		}
		setAnim(!getAnim());

		setX(getX() - getSpeed());

		break;
	case 'r':
		setDirection('r');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(96, 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(112, 16 * getTankLevel(), 16, 16));

		}
		setAnim(!getAnim());

		setX(getX() + getSpeed());

		break;
	}

	if (getX() < 0)setX(0);
	if (getX() > 624 - 48)setX(624 - 48);
	if (getY() < 0)setY(0);
	if (getY() > 624 - 48)setY(624 - 48);
	setX(getX());
	setY(getY());
	getSprite()->setPosition(getX(), getY());

}

void EnemyTank::changeDirection() {
	if (getDirection() == 'l')setDirection('d');
	else if (getDirection() == 'd')setDirection('r');
	else if (getDirection() == 'r')setDirection('u');
	else if (getDirection() == 'u')setDirection('l');
}

void EnemyTank::update(float dt) {

	if (rand() % 32 == 0 && !getReload())this->shoot(getTexture().copyToImage());

	if (getDirection() == 'u' && getY() == 0) {
		setDirection('l');
	}
	if (getDirection() == 'l' && getX() == 0) {
		setDirection('d');
	}
	if (getDirection() == 'd' && getY() == 624 - 48) {
		setDirection('r');
	}
	if (getDirection() == 'r' && getX() == 624 - 48) {
		setDirection('u');
	}
	
	if ((int)getX() % 8 == 0 && (int)getY() % 8 == 0) {

		if(rand()%64==0)changeDirection();

	}
	switch (getDirection()) {
	case 'u':
		setDirection('u');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(128, 64+16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(144, 64 + 16 * getTankLevel(), 16, 16));
		}
		setAnim(!getAnim());
		setY(getY() - getSpeed());

		break;
	case 'd':
		setDirection('d');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(192, 64 + 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(208, 64 + 16 * getTankLevel(), 16, 16));

		}
		setAnim(!getAnim());

		setY(getY() + getSpeed());

		break;
	case 'l':
		setDirection('l');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(160, 64 + 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(176, 64 + 16 * getTankLevel(), 16, 16));
		}
		setAnim(!getAnim());

		setX(getX() - getSpeed());

		break;
	case 'r':
		setDirection('r');
		if (getAnim()) {
			getSprite()->setTextureRect(IntRect(224, 64 + 16 * getTankLevel(), 16, 16));
		}
		else {
			getSprite()->setTextureRect(IntRect(240, 64 + 16 * getTankLevel(), 16, 16));

		}
		setAnim(!getAnim());

		setX(getX() + getSpeed());

		break;
	}
	if (getX() < 0)setX(0);
	if (getX() > 624 - 48)setX(624 - 48);
	if (getY() < 0)setY(0);
	if (getY() > 624 - 48)setY(624 - 48);




	setX(getX());
	setY(getY());
	
	this->setSpeed(4);

	getSprite()->setPosition(getX(), getY());
}
#include "pch.h"
#include "entity.h"

Entity::Entity(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) :entities(entities),x(x), y(y),W(W),H(H), alive(true) {

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x_image, y_image, W, H));
	sprite.setPosition(x, y);
	getSprite()->setScale(3, 3);

}

Entity::Entity(Image image, std::list <Entity*> *entities, int x_image, int y_image, int W, int H) :entities(entities), x(0), y(0), W(W), H(H), alive(true) {

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x_image, y_image, W, H));
	sprite.setPosition(x, y);
	getSprite()->setScale(3, 3);

}

Tank::Tank(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) :Entity(image,entities, x, y, x_image, y_image, W, H), speed(4), tankLevel(0) 
{
	setDirection('u');
}


void Tank::shoot(Image image) {
	getEntities()->push_back(new Bullet(this, image, getEntities(), 0, 0, 323, 102, 3, 4));
}

PlayerTank::PlayerTank(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) : Tank(image,entities, x, y, x_image, y_image, W, H) {
	setShield(false);
	setName("Player");
	setSpeed(6);
	getSprite()->setTextureRect(IntRect(0, 16 * getTankLevel(), 16, 16));
};

EnemyTank::EnemyTank(Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) : Tank(image,entities, x, y, x_image, y_image, W, H) {
	setName("Enemy");
	setSpeed(4);
	getSprite()->setTextureRect(IntRect(128, 16 * getTankLevel(), 16, 16));
};

Bullet::Bullet(Tank *player, Image image, std::list <Entity*> *entities, int x, int y, int x_image, int y_image, int W, int H) :Entity(image, entities, x, y, x_image, y_image, W, H) {
	setName("Bullet");
	player->setReload(true);
	setDirection(player->getDirection());
	setAlive(true);
	speed = 16;
	father = player;
	switch (getDirection()) {
		case 'u':
			getSprite()->setTextureRect(IntRect(323, 102, 3, 4));
			setX(player->getX() + 19);
			setY(player->getY() + 16);
			break;
		case 'd':
			getSprite()->setTextureRect(IntRect(339, 102, 3, 4));
			setX(player->getX() + 19);
			setY(player->getY() + 16);
			break;
		case 'l':
			getSprite()->setTextureRect(IntRect(330, 102, 4, 3));
			setX(player->getX() + 16);
			setY(player->getY() + 19);
			break;
		case 'r':
			getSprite()->setTextureRect(IntRect(346, 102, 4, 3));
			setX(player->getX() + 16);
			setY(player->getY() + 19);
			break;
	}

}

void Bullet::update(float dt) {
	switch (getDirection()) {
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
		if (getX() > 624-16 || getX() < 0+16 || getY() < 0+16 || getY() > 624-16) {
			setAlive(false);
			getFather()->setReload(false);
		}
		std::list <Entity*> entities = *getEntities();
		std::list <Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); it++) {
			if ((*it)->getName() == "Bullet") {
				if ((*it) == this)continue;
				if (this->getRect().intersects((*it)->getRect())) {
					(*it)->setAlive(false);
					this->setAlive(false);
					getFather()->setReload(false);
					((Bullet*)(*it))->getFather()->setReload(false);
				}
			}
			else if (father->getName() == "Player") {
				if ((*it) == this)continue;
				if ((*it) == father)continue;
				if (this->getRect().intersects((*it)->getRect())) {
					(*it)->setAlive(false);
					this->setAlive(false);
					getFather()->setReload(false);
				}
			}else if (father->getName() == "Enemy") {
				if ((*it) == this)continue;
				if ((*it)->getName()=="Enemy")continue;
				if ((*it)->getName() == "Player" && ((PlayerTank*)(*it))->hasShield() == true)continue;
				if (this->getRect().intersects((*it)->getRect())) {
					(*it)->setAlive(false);
					this->setAlive(false);
					getFather()->setReload(false);
				}
			}
		}
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

	setX(getX());
	setY(getY());



	std::list <Entity*> entities = *getEntities();
	std::list <Entity*>::iterator it;

	IntRect lol;

	for (it = entities.begin(); it != entities.end(); it++)
	{
		if (this == *it || (*it)->getName() == "Bullet")continue;
		if (this->getRect().intersects((*it)->getRect(), lol)) {
			if (this->getDirection() == 'r') {
				this->setX(lol.left - 48);
			}
			else if (this->getDirection() == 'l') {
				this->setX(lol.left + lol.width);
			}
			else if (this->getDirection() == 'u') {
				this->setY(lol.top + lol.height);
			}
			else if (this->getDirection() == 'd') {
				this->setY(lol.top - 48);
			}
		}

	}





	if (getX() < 0)setX(0);
	if (getX() > 624 - 48)setX(624 - 48);
	if (getY() < 0)setY(0);
	if (getY() > 624 - 48)setY(624 - 48);





}

void EnemyTank::changeDirection() {

	if (getDirection() == 'l') {
		switch (rand() % 3) {
			case 0:
				setDirection('d');
				break;
			case 1:
				setDirection('u');
				break;
			case 2:
				setDirection('r');
				break;
		}
	}
	else if (getDirection() == 'd'){
		switch (rand() % 3) {
		case 0:
			setDirection('u');
			break;
		case 1:
			setDirection('r');
			break;
		case 2:
			setDirection('l');
			break;
		}
	}
	else if (getDirection() == 'r'){
		switch (rand() % 3) {
		case 0:
			setDirection('d');
			break;
		case 1:
			setDirection('u');
			break;
		case 2:
			setDirection('l');
			break;
		}
	}
	else if (getDirection() == 'u') {
		switch (rand() % 3) {
		case 0:
			setDirection('d');
			break;
		case 1:
			setDirection('r');
			break;
		case 2:
			setDirection('l');
			break;
		}
	}
}

void EnemyTank::update(float dt) {
	
	if (rand() % 32 == 0 && !getReload() && this->getTReload()->getElapsedTime().asMilliseconds()>=250){
		this->getTReload()->restart();
		this->shoot(getTexture().copyToImage());
	};

	if (getDirection() == 'u' && getY() == 0) {
		switch (rand() % 2) {
		case 0:
			setDirection('r');
			break;
		case 1:
			setDirection('d');
			break;
		}
	}
	if (getDirection() == 'l' && getX() == 0) {
		switch (rand() % 2) {
		case 0:
			setDirection('u');
			break;
		case 1:
			setDirection('l');
			break;
		}
	}
	if (getDirection() == 'd' && getY() == 624 - 48) {
		switch (rand() % 2) {
		case 0:
			setDirection('r');
			break;
		case 1:
			setDirection('u');
			break;
		}
	}
	if (getDirection() == 'r' && getX() == 624 - 48) {
		switch (rand() % 2) {
		case 0:
			setDirection('u');
			break;
		case 1:
			setDirection('l');
			break;
		}
	}
	
	if ((int)getX() % 24 == 0 && (int)getY() % 24 == 0) {

		if(rand()%16==0)changeDirection();

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


	setX(getX());
	setY(getY());
	

	std::list <Entity*> entities = *getEntities();
	std::list <Entity*>::iterator it;

	IntRect lol;

	for (it = entities.begin(); it != entities.end(); it++)
	{
		if (this == *it || (*it)->getName()=="Bullet")continue;
		if ((*it)->getName() == "Player" && (*it)->isAlive() == false)continue;
		if (this->getRect().intersects((*it)->getRect(), lol)) {
			if (this->getDirection() == 'r') {
				this->setX(lol.left - 48);
			}
			else if (this->getDirection() == 'l') {
				this->setX(lol.left + lol.width);
			}
			else if (this->getDirection() == 'u') {
				this->setY(lol.top + lol.height);
			}
			else if (this->getDirection() == 'd') {
				this->setY(lol.top - 48);
			}
			if (rand() % 16 == 0)
				switch (this->getDirection()) {
					case 'l':
						this->setDirection('r');
						break;
					case 'r':
						this->setDirection('l');
						break;
					case 'd':
						this->setDirection('u');
						break;
					case 'u':
						this->setDirection('d');
						break;
				}
		}

	}

	if (getX() < 0)setX(0);
	if (getX() > 624 - 48)setX(624 - 48);
	if (getY() < 0)setY(0);
	if (getY() > 624 - 48)setY(624 - 48);


}
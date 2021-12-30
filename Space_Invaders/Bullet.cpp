#include "Bullet.h"

//Constructor
Bullet::Bullet(float initX, float initY, float speed, std::string direction, sf::Color color) {
	this->speed = speed;
	this->direction = direction;
	this->bullet.setSize(sf::Vector2f(5, 10));
	this->bullet.setPosition(initX, initY);
	this->bullet.setFillColor(color);
}

//Destructor
Bullet::~Bullet() {
}

sf::RectangleShape Bullet::getBullet() {
	return bullet;
}

int Bullet::getXPosition() {
	return bullet.getPosition().x;
}

int Bullet::getYPosition() {
	return bullet.getPosition().y;
}

void Bullet::update() {
	//Move the bullet up or down
	if (direction == "Up") {
		bullet.move(0, -speed);
	}
	else {
		bullet.move(0, speed);
	}
}

void Bullet::render(sf::RenderTarget& target) {
	target.draw(bullet);
}

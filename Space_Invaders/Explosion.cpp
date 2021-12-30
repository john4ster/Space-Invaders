#include "Explosion.h"

//Method to initialize the explosion texture
void Explosion::initTexture() {
	if (!texture.loadFromFile("Textures/explosion.png")) {
		std::cout << "Error loading player texture";
	}
}

//Method to initialize the explosion sprite
void Explosion::initSprite(int xPosition, int yPosition) {
	sprite.setTexture(this->texture);
	sprite.scale(4.0f, 4.0f);
	sprite.setPosition(xPosition, yPosition);
}

//Constructor
Explosion::Explosion(int xPosition, int yPosition) {
	initTexture();
	initSprite(xPosition, yPosition);
	durationCounter.restart();
}

//Destructor
Explosion::~Explosion() {
}

//Method to check if explosion is over
bool Explosion::explosionOver() {
	if (durationCounter.getElapsedTime().asMilliseconds() >= 200) {
		return true;
	}
	else {
		return false;
	}
}

void Explosion::render(sf::RenderTarget& target) {
	target.draw(sprite);
}
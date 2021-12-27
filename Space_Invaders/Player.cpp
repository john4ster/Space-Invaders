#include "Player.h"

//Get texture to be used for the sprite
void Player::initTexture() {
	if (!texture.loadFromFile("Textures/player.png")) {
		std::cout << "Error loading player texture";
	}
}

//Create, scale, and set position of sprite
void Player::initSprite() {
	sprite.setTexture(this->texture);
	sprite.scale(5.0f, 5.0f);
	sprite.setPosition(415.f, 765.f);
}

//Initialize the player vertices that will be used as a hitbox
void Player::initVertices() {
	vertices = sf::VertexArray(sf::Lines, 8);
	//Top horizontal line
	vertices[0].position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
	vertices[1].position = sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y);
	//Bottom horizontal line
	vertices[2].position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 60);
	vertices[3].position = sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y + 60);
	//Left vertical line
	vertices[4].position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
	vertices[5].position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 60);
	//Right vertical line
	vertices[6].position = sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y);
	vertices[7].position = sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y + 60);
}

//Constructor
Player::Player() {
	movementSpeed = 2.f;
	lives = 3;
	initTexture();
	initSprite();
	initVertices();
}

//Destructor
Player::~Player() {
}

sf::VertexArray Player::getVertices() {
	return vertices;
}

//Gets gun position to shoot from since the default x position is not the center of the sprite
int Player::getGunXPosition() {
	return sprite.getPosition().x + 37.5; //Returns x position plus an offset to return center of gun position
}

int Player::getXPosition() {
	return sprite.getPosition().x;
}

int Player::getYPosition() {
	return sprite.getPosition().y;
}

int Player::getLives() {
	return lives;
}

void Player::subtractLife() {
	lives--;
}

//Move the player
void Player::move(float xDirection) {
	sprite.move((xDirection * movementSpeed), 0);
	initVertices();
}

//Draw the player to the screen
void Player::render(sf::RenderTarget& target) {
	target.draw(sprite);
}

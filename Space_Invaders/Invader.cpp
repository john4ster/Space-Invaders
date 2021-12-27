#include "Invader.h"

//Pulls texture from textures folder to be used on the sprite
void Invader::initTexture() {
	if (!this->texture.loadFromFile("Textures/invaderSpriteSheet.png")) {
		std::cout << "Error loading invader texture";
	}
}

//Initializes sprite based on invader type
void Invader::initSprite() {
	sprite.setTexture(texture);
	//Sprite is dependent on the invader size, small, medium, or large
	if (invaderType == "Large") {
		currentSpriteRect = sf::IntRect(0, 0, 16, 16);
	}
	else if (invaderType == "Medium") {
		currentSpriteRect = sf::IntRect(0, 16, 16, 16);
	}
	else if (invaderType == "Small") {
		currentSpriteRect = sf::IntRect(0, 32, 16, 16);
	}
	//Set up and scale the sprite
	sprite.setTextureRect(sf::IntRect(currentSpriteRect));
	sprite.scale(4.0f, 4.0f);
}

//Initializes the vertices of the invader, these will be used as a hitbox
void Invader::initVertices() {
	//Sprites aren't draw right on the edge of the spritesheet, 
	//so sheetOffset offsets that to draw a more accurate hitbox
	int sheetOffset = 5;
	vertices = sf::VertexArray(sf::Lines, 8);
	//Top horizontal line
	vertices[0].position = sf::Vector2f(sprite.getPosition().x + sheetOffset, sprite.getPosition().y);
	vertices[1].position = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y);
	//Bottom horizontal line
	vertices[2].position = sf::Vector2f(sprite.getPosition().x + sheetOffset, sprite.getPosition().y + 60);
	vertices[3].position = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y + 60);
	//Left vertical line
	vertices[4].position = sf::Vector2f(sprite.getPosition().x + sheetOffset, sprite.getPosition().y);
	vertices[5].position = sf::Vector2f(sprite.getPosition().x + sheetOffset, sprite.getPosition().y + 60);
	//Right vertical line
	vertices[6].position = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y);
	vertices[7].position = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y + 60);
}

//Update the current sprite for animation
void Invader::updateSprite() {
	//Use the animation clock to space out time between sprites
	if (animationClock.getElapsedTime().asMilliseconds() > 300) {
		//Figure out which part of the sprite sheet to use based on the current sprite and size of invader
		//Large invaders
		if (invaderType == "Large") {
			if (currentSpriteRect == sf::IntRect(0, 0, 16, 16)) {
				currentSpriteRect = sf::IntRect(16, 0, 16, 16);
			}
			else {
				currentSpriteRect = sf::IntRect(0, 0, 16, 16);
			}
		}
		//Medium invaders
		if (invaderType == "Medium") {
			if (currentSpriteRect == sf::IntRect(0, 16, 16, 16)) {
				currentSpriteRect = sf::IntRect(16, 16, 16, 16);
			}
			else {
				currentSpriteRect = sf::IntRect(0, 16, 16, 16);
			}
		}
		//Small invaders
		if (invaderType == "Small") {
			if (currentSpriteRect == sf::IntRect(0, 32, 16, 16)) {
				currentSpriteRect = sf::IntRect(16, 32, 16, 16);
			}
			else {
				currentSpriteRect = sf::IntRect(0, 32, 16, 16);
			}
		}
		//Change the sprite to the next sprite and restart the animation clock
		sprite.setTextureRect(currentSpriteRect);
		animationClock.restart();
	}
}

//Constructor
Invader::Invader(std::string type) {
	invaderType = type;
	movementDirection = "right";
	initTexture();
	initSprite();
}

//Destructor
Invader::~Invader() {
}

sf::VertexArray Invader::getVertices() {
	return vertices;
}

void Invader::setPosition(float x, float y) {
	sprite.setPosition(x, y);
	initVertices();
}

int Invader::getCenterXPosition() {
	return sprite.getPosition().x + 37.5;
}

int Invader::getXPosition() {
	return sprite.getPosition().x;
}

int Invader::getYPosition() {
	return sprite.getPosition().y;
}

//Returns score value based on the invader tpye
int Invader::getScoreValue() {
	if (invaderType == "Small") {
		return 30;
	}
	else if (this->invaderType == "Medium") {
		return 20;
	}
	else if (this->invaderType == "Large") {
		return 10;
	}
}

//Changes current direction of invader so it goes the opposite way
void Invader::changeDirection() {
	if (movementDirection == "right") {
		movementDirection = "left";
	}
	else {
		movementDirection = "right";
	}
}

//Move the invader
void Invader::move(float xDirection, float yDirection) {
	if (movementDirection == "right") {
		sprite.move(xDirection, yDirection);
	}
	else {
		sprite.move(-xDirection, yDirection);
	}
	//Update the current sprite for animation, and re-initialize the vertices
	updateSprite();
	initVertices();
}

//Draw the invader to the screen
void Invader::render(sf::RenderTarget& target) {
	target.draw(sprite);
}
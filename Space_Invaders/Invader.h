#pragma once
# include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//The invader class is used to make individual invaders and handle their sprites, animations, hitboxes, and movement
class Invader {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		//Variables used to handle animation
		sf::IntRect currentSpriteRect;
		sf::Clock animationClock;
		//Handle invaderType, vertices (hitbox), and movementDirection (left or right)
		std::string invaderType;
		sf::VertexArray vertices;
		std::string movementDirection;

		//Initialize variables
		void initTexture();
		void initSprite();
		void initVertices();
		//Update the sprite, used for animation
		void updateSprite();
	public:
		Invader(std::string type);
		~Invader();

		sf::VertexArray getVertices();
		//Methods used to set and get position information of invaders
		void setPosition(float x, float y);
		int getCenterXPosition();
		int getXPosition();
		int getYPosition();
		//Returns score value of invader based on the invader type
		int getScoreValue();
		//Methods used to change the direction of the invader and move it
		void changeDirection();
		void move(float xDirection, float yDirection);
		//Render the invader onto the window
		void render(sf::RenderTarget& target);
};
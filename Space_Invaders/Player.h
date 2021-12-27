#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//The player class handles the player's movement, vertices (hitbox), and lives
class Player {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		float movementSpeed;
		int lives;
		sf::VertexArray vertices;

		//Initialize variables
		void initTexture();
		void initSprite();
		void initVertices();
	public:
		Player();
		~Player();

		sf::VertexArray getVertices();
		//Methods used to get the player's position information
		int getGunXPosition();
		int getXPosition();
		int getYPosition();
		//Methods used to get the player's current lives and subtract lives
		int getLives();
		void subtractLife();
		//Method used to move the player
		void move(float xDirection);
		//Render the player onto the window
		void render(sf::RenderTarget& target);
};

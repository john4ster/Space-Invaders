#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Explosion {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Clock durationCounter; //Timer to keep track of the duration of the explosion

		//Initialize variables
		void initTexture();
		void initSprite(int xPosition, int yPosition);
	public:
		Explosion(int xPosition, int yPosition);
		~Explosion();

		bool explosionOver(); //Method to check if the explosion is over
		void render(sf::RenderTarget& target); //Render the explosion onto the window
};
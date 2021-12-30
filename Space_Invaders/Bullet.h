#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

	//The bullet class is used for both the invader's bullets and the player's bullets
class Bullet {
	private:
		sf::RectangleShape bullet;
		float speed;
		std::string direction;

	public:
		Bullet(float initX, float initY, float speed, std::string direction, sf::Color color);
		~Bullet();

		sf::RectangleShape getBullet();
		int getXPosition();
		int getYPosition();
		void update();
		void render(sf::RenderTarget& target);
};

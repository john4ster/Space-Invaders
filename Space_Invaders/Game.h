#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Player.h"
#include "Invader.h"
#include "Bullet.h"

//The game class handles all game objects such as the player, invaders, and bullets, as well as collisions
class Game {
	private:
		int windowWidth;
		int windowHeight;
		sf::RenderWindow* window;
		Player* player;
		int score;
		bool gameOver;
		//Font and texts to be displayed to the screen
		sf::Font* machineFont;
		sf::Text* livesText;
		sf::Text* gameOverText;
		sf::Text* scoreText;

		//Vectors that hold the invaders and bullets
		std::vector <std::vector<Invader*>> invaders;
		std::vector <Bullet*> playerBullets;
		std::vector <Bullet*> invaderBullets;
		//Cooldown timer to be used for the player and invader shooting cooldown
		sf::Clock playerCoolDown;
		sf::Clock invaderCoolDown;

		//Keep track of delta time to move entities independent of framerate
		sf::Clock dtClock;
		float dt;

		//Initialize variables
		void initWindow();
		void initPlayer();
		void initText();
		void initInvaders();
		void initShields();
		//Check collisions and if the player has lost
		void checkCollisions();
		void checkLoseConditions();
		//Update functions to update bullets, player and invader positions, and text
		void randomizeInvaderBullets();
		void updateInput();
		void updateText();
		void updateBullets();
		void updateInvaders();
		void update();
		//Render to the window
		void render();
	public:
		Game();
		~Game();

		void run();
};


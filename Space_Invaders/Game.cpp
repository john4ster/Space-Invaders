#include "Game.h"

//Create window
void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight),
		"Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
}

//Create player
void Game::initPlayer() {
	player = new Player();
}

//Initialize font, livesText, scoreText, and gameOverText
void Game::initText() {
	//Load font from file
	machineFont = new sf::Font();
	if (!(*machineFont).loadFromFile("Fonts/machineFont.ttf")) {
		std::cout << "Error loading score font";
	}
	//Setup lives text
	livesText = new sf::Text();
	livesText->setFont(*machineFont);
	livesText->setCharacterSize(20);
	livesText->setStyle(sf::Text::Bold);
	livesText->setFillColor(sf::Color::White);
	livesText->setPosition(windowWidth - 110, 0);
	livesText->setString("Lives: " + std::to_string(player->getLives()));
	//Setup score text
	scoreText = new sf::Text();
	scoreText->setFont(*machineFont);
	scoreText->setCharacterSize(20);
	scoreText->setStyle(sf::Text::Bold);
	scoreText->setFillColor(sf::Color::White);
	scoreText->setPosition(0, 0);
	scoreText->setString("Score: " + std::to_string(score));
	//Setup game over text
	gameOverText = new sf::Text();
	gameOverText->setFont(*machineFont);
	gameOverText->setCharacterSize(50);
	gameOverText->setStyle(sf::Text::Bold);
	gameOverText->setFillColor(sf::Color::White);
	gameOverText->setPosition(300, 300);
	gameOverText->setString("Game Over");
}

//Populate invaders vector with invaders
void Game::initInvaders() {
	//Invaders are stored in a 2d vector, the invaders vector contains 5 vectors (each of these vectors is a row) 
	//and each vector has 11 invaders
	//Initialize 5 vectors/rows
	for (int i = 0; i < 5; i++) {
		invaders.push_back(std::vector <Invader*>());
	}
	//Add invaders to each row
	//Add first row (small invaders)
	for (int i = 0; i < 11; i++) {
		invaders[0].push_back(new Invader("Small"));
		invaders[0][i]->setPosition(i * 80, 50);
	}
	//Add second and third row (medium invaders)
	for (int i = 0; i < 11; i++) {
		invaders[1].push_back(new Invader("Medium"));
		invaders[1][i]->setPosition(i * 80, 100);
	}
	for (int i = 0; i < 11; i++) {
		invaders[2].push_back(new Invader("Medium"));
		invaders[2][i]->setPosition(i * 80, 150);
	}
	//Add fourth and fifth rows (large invaders)
	for (int i = 0; i < 11; i++) {
		invaders[3].push_back(new Invader("Large"));
		invaders[3][i]->setPosition(i * 80, 200);
	}
	for (int i = 0; i < 11; i++) {
		invaders[4].push_back(new Invader("Large"));
		invaders[4][i]->setPosition(i * 80, 250);
	}
}

//Constructor
Game::Game() {
	windowWidth = 900;
	windowHeight = 800;
	score = 0;
	gameOver = false;
	initWindow();
	initPlayer();
	initText();
	initInvaders();
}

//Destructor
Game::~Game() {
	delete window;
	delete player;
}

//Run the game loop
void Game::run() {
	while (window->isOpen()) {
		dt = dtClock.restart().asSeconds();
		update();
		render();
	}
}

//Checks all collisions in game between bullets, the player, and invaders
void Game::checkCollisions() {

	//Check collisions with each invader
	for (int i = 0; i < invaders.size(); i++) {
		for (int j = 0; j < invaders[i].size(); j++) {
			sf::VertexArray invaderHitbox = invaders[i][j]->getVertices();
			//See if player bullets are hitting the invader, if they are, update score 
			//and delete the invader and bullet
			for (int k = 0; k < playerBullets.size(); k++) {
				if (playerBullets[k]->getBullet().getGlobalBounds().intersects(invaderHitbox.getBounds())) {
					//Update the score
					score += invaders[i][j]->getScoreValue();
					updateText();
					//Add an explosion where the bullet hit
					explosions.push_back(new Explosion(playerBullets[k]->getXPosition(), playerBullets[k]->getYPosition()));
					//Delete the bullet
					delete playerBullets[k];
					playerBullets.erase(playerBullets.begin() + k);
					//Delete the invader
					delete invaders[i][j];
					invaders[i].erase(invaders[i].begin() + j);
				}
			}
		}
	}

	//Check collisions with player
	sf::VertexArray playerHitbox = player->getVertices();
	for (int i = 0; i < invaderBullets.size(); i++) {
		if (invaderBullets[i]->getBullet().getGlobalBounds().intersects(playerHitbox.getBounds())) {
			//Add an explosion where the bullet hit
			explosions.push_back(new Explosion(invaderBullets[i]->getXPosition(), invaderBullets[i]->getYPosition()));
			//Delete the bullet and subtract a life from the player
			delete invaderBullets[i];
			invaderBullets.erase(invaderBullets.begin() + i);
			player->subtractLife();
		}
	}
}

//See if the player has lost, either by having 0 lives or the invaders reaching the bottom of the screen
void Game::checkLoseConditions() {
	//Check if player lives goes to 0
	if (player->getLives() <= 0) {
		gameOver = true;
	}
	//Check if invaders reach player
	//Use sprite difference since the player and invader y positions are slightly offset by 15 due to sprite sizes
	int spriteDifference = 5;
	for (int i = 0; i < invaders.size(); i++) {
		for (int j = 0; j < invaders[i].size(); j++) {
			if (invaders[i][j]->getYPosition() - spriteDifference == player->getYPosition()) {
				gameOver = true;
			}
		}
	}

}

//Pick a random invader to shoot a bullet from
void Game::randomizeInvaderBullets() {
	//Check invader cool down
	if (invaderCoolDown.getElapsedTime().asMilliseconds() > 500) {
		//Select a random invader to fire the bullet
		int row = rand() % invaders.size();
		//Make sure the row has invaders
		int col = 0;
		if (invaders[row].size() != 0) {
			col = rand() % invaders[row].size();
		}
		//Make sure invader still exists
		if (row < invaders.size() && col < invaders[row].size()) {
			invaderBullets.push_back(new Bullet(invaders[row][col]->getCenterXPosition(), invaders[row][col]->getYPosition(),
				(1000 * dt), "Down", sf::Color::White));
		}
		//Restart cooldown
		invaderCoolDown.restart();
	}
}

//Listen for player input
void Game::updateInput() {
	//Movement controls
	//Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (player->getXPosition() < (windowWidth - 80)) { //Stop player from going off screen
			player->move(200 * dt);
		}
	}
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (player->getXPosition() > 0) { //Stop player from going off screen
			player->move(-200 * dt);
		}
	}
	//Shooting controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		//Check cooldown timer
		if (playerCoolDown.getElapsedTime().asMilliseconds() > 200) {
			//Add a new bullet to the bullets vector
			playerBullets.push_back(new Bullet(player->getGunXPosition(), player->getYPosition(),
				(1000 * dt), "Up", sf::Color::Green));
			//Restart cooldown timer
			playerCoolDown.restart();
		}
	}
}

//Update text to keep up with lives and score info
void Game::updateText() {
	livesText->setString("Lives: " + std::to_string(player->getLives()));
	scoreText->setString("Score: " + std::to_string(score));
}

//Update bullet positions (both invader bullets and player bullets)
void Game::updateBullets() {
	//Update each player bullet
	for (int i = 0; i < playerBullets.size(); i++) {
		playerBullets[i]->update();
		//If the player bullet is past the top of the screen, delete it
		if (playerBullets[i]->getBullet().getGlobalBounds().top < 0.f) {
			delete playerBullets[i]; //Remove the bullet from memory
			playerBullets.erase(playerBullets.begin() + i); //Remove the pointer from the bullets vector
		}
	}
	//Update each invader bullet
	for (int i = 0; i < invaderBullets.size(); i++) {
		invaderBullets[i]->update();
	}
}

//Update invader positions
void Game::updateInvaders() {
	//If all invaders have been killed, spawn more
	if (invaders[0].size() == 0 && invaders[1].size() == 0 && invaders[2].size() == 0 && invaders[3].size() == 0 && invaders[4].size() == 0) {
		initInvaders();
}
	//Left and right borders of the screen, this is where invaders move down to the next row
	//These numbers also have to account for the invader hitboxes
	int rightBorder = windowWidth - 50;
	int leftBorder = -5;
	//Variables for how much in the x and y directions the invaders should move
	int verticalStep = 40;
	//Loop through each row
	for (int i = 0; i < invaders.size(); i++) {
		//Loop through each invader in each row and move them
		for (int j = 0; j < invaders[i].size(); j++) {
			invaders[i][j]->move(0.1, 0);
			//If the invaders are at the edge of the screen, change their direction and move them down
			if (invaders[i][j]->getXPosition() >= rightBorder || invaders[i][j]->getXPosition() <= leftBorder) {
				//Loop through each row again
				for (int k = 0; k < invaders.size(); k++) {
					//Change direction and move each invader in each row
					for (int l = 0; l < invaders[k].size(); l++) {
						invaders[k][l]->changeDirection();
						invaders[k][l]->move(0, verticalStep);
					}
				}
			}
		}
	}
}

//Update explosions, removing ones that are at the end of their duration
void Game::updateExplosions() {
	for (int i = 0; i < explosions.size(); i++) {
		if (explosions[i]->explosionOver()) {
			delete explosions[i];
			explosions.erase(explosions.begin() + i);
		}
	}
}

//Update the game
void Game::update() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
	if (gameOver == false) {
		updateInput();
		updateText();
		randomizeInvaderBullets();
		checkCollisions();
		checkLoseConditions();
		updateBullets();
		updateInvaders();
		updateExplosions();
	}
}

//Draw to the screen
void Game::render() {
	window->clear();

	//Display game over screen if game has ended
	if (gameOver) {
		scoreText->setPosition(400, 400);
		window->draw(*gameOverText);
		window->draw(*scoreText);
	}
	//Otherwise, display game
	else {
		player->render(*window);

		//Render lives
		window->draw(*livesText);

		//Render current score
		window->draw(*scoreText);

		//Render invaders
		for (int i = 0; i < invaders.size(); i++) {
			for (int j = 0; j < invaders[i].size(); j++) {
				invaders[i][j]->render(*window);
			}
		}

		//Render player bullets
		for (int i = 0; i < playerBullets.size(); i++) {
			playerBullets[i]->render(*window);
		}

		//Render invader bullets
		for (int i = 0; i < invaderBullets.size(); i++) {
			invaderBullets[i]->render(*window);
		}

		//Render explosions
		for (int i = 0; i < explosions.size(); i++) {
			explosions[i]->render(*window);
		}
	}

	window->display();
}
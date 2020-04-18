#include "Game.h"

#include "State.h"
#include "PlayState.h"
#include <iostream>
#include <algorithm>

Game::Game() {
	// Create game window
	//window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "LD64", sf::Style::Fullscreen);
	window = new sf::RenderWindow(sf::VideoMode(960, 540), "LD64");
	window->setFramerateLimit(60);
	fullscreen = false;
	scale = std::min(window->getSize().x / 240, window->getSize().y / 135);

	// Initialize game-wide variables

	// Initial state
	changeState(new PlayState());

	// Start the clock
	sf::Clock clock;

	while (window->isOpen()) {
		// State
		if (nextState) {
			// Load up the new state
			if (state)
				delete state;
			state = nextState;
			nextState = nullptr;
			state->setGame(this);
			state->init();

			// Restart the clock to account for load time
			//clock.restart();
		}

		// Event
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				exit();
			}
			else if (event.type == sf::Event::Resized) {
				window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::F11) {
					if (fullscreen) {
						delete window;
						window = new sf::RenderWindow(sf::VideoMode(960, 540), "LD64");
						window->setFramerateLimit(60);
						fullscreen = false;
					}
					else {
						delete window;
						window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "LD64", sf::Style::Fullscreen);
						window->setFramerateLimit(60);
						fullscreen = true;
					}
				}
			}

			if (state) {
				state->gotEvent(event);
			}
		}

		// Update
		sf::Time elapsed = clock.restart();
		// If the game freezes, make sure no time passes
		if (elapsed.asMilliseconds() >= 250) {
			elapsed = sf::Time::Zero;
		}
		if (state)
			state->update(elapsed);

		// Render
		window->clear();
		if (state) {
			state->render(*window);
		}

		// Pixelate
		sf::Texture postTexture;
		postTexture.create(window->getSize().x, window->getSize().y);
		postTexture.update(*window);

		sf::RectangleShape overlay;
		overlay.setFillColor(sf::Color::Black);
		overlay.setSize(sf::Vector2f(window->getSize()));
		window->draw(overlay);

		sf::Sprite postSprite(postTexture, sf::IntRect(0, 0, 240, 135));
		scale = std::min(window->getSize().x / 240, window->getSize().y / 135);
		postSprite.setScale(scale, scale);
		postSprite.setPosition(window->getSize().x / 2 - postSprite.getGlobalBounds().width / 2, window->getSize().y / 2 - postSprite.getGlobalBounds().height / 2);
		screenOffset = postSprite.getPosition();
		window->draw(postSprite);

		window->display();

		// Exit
		if (exiting) {
			window->close();
		}
	}
}


Game::~Game() {
	if (state)
		delete state;
	if (nextState)
		delete nextState;

	delete window;
}

sf::RenderWindow *Game::getWindow() {
	return window;
}

void Game::changeState(State *newState) {
	if (nextState)
		delete nextState;
	nextState = newState;
}

void Game::exit() {
	exiting = true;
}

sf::Texture& Game::loadTexture(std::string filename) {
	if (textures.count(filename) == 0) {
		sf::Texture newTexture;
		if (newTexture.loadFromFile(filename)) {
			textures.insert(std::pair<std::string, sf::Texture>(filename, newTexture));
			// Debug
			//std::cout << "New texture created (" << filename << ")\n";
		}
		else {
			if (textures.count("BadTexture") == 0) {
				sf::Image badImage;
				badImage.create(2, 2, sf::Color::Black);
				badImage.setPixel(0, 0, sf::Color::Cyan);
				badImage.setPixel(1, 1, sf::Color::Cyan);
				newTexture.loadFromImage(badImage);
				newTexture.setRepeated(true);
				textures.insert(std::pair<std::string, sf::Texture>("BadTexture", newTexture));

				// Debug
				//std::cout << "Bad texture created (" << filename << ")\n";
			}
			else {
				// Debug
				//std::cout << "Bad texture loaded (" << filename << ")\n";
			}
			return textures["BadTexture"];
		}
	}
	else {
		// Debug
		//std::cout << "Existing texture loaded (" << filename << ")\n";
	}
	return textures[filename];
}

sf::SoundBuffer& Game::loadSoundBuffer(std::string filename) {
	if (soundBuffers.count(filename) == 0) {
		sf::SoundBuffer newSoundBuffer;
		if (newSoundBuffer.loadFromFile(filename)) {
			soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>(filename, newSoundBuffer));
			// Debug
			//std::cout << "New sound buffer created (" << filename << ")\n";
		}
		else {
			// Debug
			//std::cout << "Cannot create sound buffer (" << filename << ")\n";
		}
	}
	else {
		// Debug
		//std::cout << "Existing sound buffer loaded (" << filename << ")\n";
	}
	return soundBuffers[filename];
}

sf::Vector2u Game::screenSize() {
	return window->getSize();
}

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <map>

class State;

class Game {
public:
	Game();
	~Game();

	sf::RenderWindow *getWindow();
	void changeState(State *newState);
	void exit();

	sf::Texture& loadTexture(std::string filename);
	sf::SoundBuffer& loadSoundBuffer(std::string filename);

	sf::Vector2u screenSize();
	int scale;
	sf::Vector2f screenOffset;

	// Game Variables

private:
	sf::RenderWindow *window;
	bool fullscreen;

	State *state = nullptr;
	State *nextState = nullptr;
	bool exiting = false;

	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
};

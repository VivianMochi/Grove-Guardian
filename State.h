#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class State {
public:
	State();
	virtual ~State();

	virtual void init() = 0;
	virtual void gotEvent(sf::Event event) = 0;
	virtual void update(sf::Time elapsed) = 0;
	virtual void render(sf::RenderWindow &window) = 0;

	sf::Texture& loadTexture(std::string filename);
	sf::SoundBuffer& loadSoundBuffer(std::string filename);

	void setGame(Game *game);
	Game *getGame();

protected:
	Game *game = nullptr;
};


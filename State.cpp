#include "State.h"

State::State() {

}

State::~State() {

}

sf::Texture& State::loadTexture(std::string filename) {
	return game->loadTexture(filename);
}

sf::SoundBuffer& State::loadSoundBuffer(std::string filename) {
	return game->loadSoundBuffer(filename);
}

void State::setGame(Game *game) {
	this->game = game;
}

Game *State::getGame() {
	return game;
}

#include "Hud.h"

#include "PlayState.h"

Hud::Hud() {

}

Hud::~Hud() {

}

void Hud::init() {
	topHudSprite.setTexture(state->loadTexture("Resource/Image/TopHud.png"));
	topHudSprite.setTextureRect(sf::IntRect(0, 0, 240, 20));

	topHudBg.setTexture(state->loadTexture("Resource/Image/TopHud.png"));
	topHudBg.setTextureRect(sf::IntRect(0, 20, 240, 20));
}

void Hud::update(sf::Time elapsed) {

}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(topHudBg);
	target.draw(topHudSprite);
}

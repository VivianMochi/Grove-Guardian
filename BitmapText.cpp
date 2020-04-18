#include "BitmapText.h"

#include <cctype>

BitmapText::BitmapText() {

}

BitmapText::BitmapText(const sf::Texture &texture, std::string text) {
	setTexture(texture);
	setText(text);
}

BitmapText::~BitmapText() {

}

void BitmapText::setTexture(const sf::Texture &texture) {
	this->texture = &texture;
}

void BitmapText::setText(std::string text) {
	this->text = text;
}

void BitmapText::setColor(sf::Color color) {
	this->color = color;
}

std::string BitmapText::getText() {
	return this->text;
}

void BitmapText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	sf::Vector2f currentPosition = getPosition();
	if (texture) {
		sf::Sprite glyph(*texture);
		glyph.setColor(color);
		for (int i = 0; i < text.length(); i++) {
			glyph.setPosition(currentPosition);
			char character = std::toupper(text[i]);
			if (character < '@') {
				glyph.setTextureRect(sf::IntRect(8 * (character - ' '), 0, 8, 8));
			}
			else {
				glyph.setTextureRect(sf::IntRect(8 * (character - '@'), 8, 8, 8));
			}
			target.draw(glyph, states);

			if (character == '\n') {
				currentPosition.x = getPosition().x;
				currentPosition.y += 12;
			}
			else if (character == '\t') {
				currentPosition.x = getPosition().x + (int)(currentPosition.x - getPosition().x) / 28 * 28 + 28;
			}
			else if (character == '!' || character == '.' || character == ':' || character == ';') {
				currentPosition.x += 3;
			}
			else if (character == '(' || character == ')' || character == '/' || character == '[' || character == '\\' || character == ']') {
				currentPosition.x += 4;
			}
			else if (character == '1' || character == 'I') {
				currentPosition.x += 5;
			}
			else if (character == 'M' || character == 'W') {
				currentPosition.x += 8;
			}
			else {
				currentPosition.x += 7;
			}
		}
	}
}

#include "Hud.h"

#include "PlayState.h"
#include "TreeInfo.h"
#include "Ruin.h"

void Hud::init() {
	dayBarSprite.setTexture(state->loadTexture("Resource/Image/DayBar.png"));
	dayBarSprite.setTextureRect(sf::IntRect(0, 0, 124, 10));
	dayBarSprite.setPosition(58, 0);

	dayBar.setFillColor(sf::Color(200, 200, 200));
	dayBar.setPosition(dayBarSprite.getPosition() + sf::Vector2f(3, 3));

	dayBarBg.setTexture(state->loadTexture("Resource/Image/DayBar.png"));
	dayBarBg.setTextureRect(sf::IntRect(0, 40, 124, 10));
	dayBarBg.setPosition(58, 0);

	sunSprite.setTexture(state->loadTexture("Resource/Image/DayBar.png"));
	sunSprite.setTextureRect(sf::IntRect(0, 10, 16, 8));
	sunSprite.setPosition(dayBarSprite.getPosition() + sf::Vector2f(state->hour * 11 - 1, 9));

	fastButton.setTexture(state->loadTexture("Resource/Image/FastButton.png"));
	fastButton.setTextureRect(sf::IntRect(0, 0, 12, 10));
	fastButton.setPosition(48, 0);

	resourcesHud.setTexture(state->loadTexture("Resource/Image/ResourcesHud.png"));

	dayText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	dayText.setColor(sf::Color::White);
	dayText.setPosition(4, 4);

	lightText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	lightText.setColor(state->getResourceColor("Light"));
	lightText.setPosition(14, 18);

	lightDeltaText = lightText;
	lightDeltaText.setPosition(-100, -100);

	waterText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	waterText.setColor(state->getResourceColor("Water"));
	waterText.setPosition(14, 28);

	waterDeltaText = waterText;
	waterDeltaText.setPosition(-100, -100);

	nutrientsText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	nutrientsText.setColor(state->getResourceColor("Nutrients"));
	nutrientsText.setPosition(14, 38);

	nutrientsDeltaText = nutrientsText;
	nutrientsDeltaText.setPosition(-100, -100);

	infoPane.setTexture(state->loadTexture("Resource/Image/InfoPane.png"));
	infoPane.setPosition(240, 135 - infoPane.getTexture()->getSize().y);
	infoTitle = dayText;
	infoDescription = dayText;
	upgrade1Text = infoTitle;
	upgrade2Text = infoTitle;
	upgrade3Text = infoTitle;
	costPane.setTexture(state->loadTexture("Resource/Image/Cost.png"));

	lastLight = state->light;
	lastWater = state->water;
	lastNutrients = state->nutrients;
}

void Hud::update(sf::Time elapsed) {
	dayBar.setSize(sf::Vector2f(11 * state->hour + std::floor(8 * state->time / state->secondsPerDay), 4));

	if (state->weather == PlayState::sunny) {
		dayBarSprite.setTextureRect(sf::IntRect(0, 0, 124, 10));
	}
	else if (state->weather == PlayState::rainy) {
		dayBarSprite.setTextureRect(sf::IntRect(0, 20, 124, 10));
	}
	if (state->getTimeOfDay(state->hour) == "Night") {
		sunSprite.setTextureRect(sf::IntRect(32, 10, 16, 8));
	}
	else if (state->getTimeOfDay(state->hour) == "Transition") {
		if (state->weather == PlayState::sunny) {
			sunSprite.setTextureRect(sf::IntRect(16, 10, 16, 8));
		}
		else if (state->weather == PlayState::rainy) {
			sunSprite.setTextureRect(sf::IntRect(48, 10, 16, 8));
		}
	}
	else {
		if (state->weather == PlayState::sunny) {
			sunSprite.setTextureRect(sf::IntRect(0, 10, 16, 8));
		}
		else if (state->weather == PlayState::rainy) {
			sunSprite.setTextureRect(sf::IntRect(48, 10, 16, 8));
		}
	}
	sf::Vector2f sunSpriteDesiredLocation = dayBarSprite.getPosition() + sf::Vector2f(state->hour * 11 - 1, 9);
	if (sunSpriteDesiredLocation.x < dayBarSprite.getPosition().x + 1) {
		sunSpriteDesiredLocation.x = dayBarSprite.getPosition().x + 1;
	}
	else if (sunSpriteDesiredLocation.x > dayBarSprite.getPosition().x + 107) {
		sunSpriteDesiredLocation.x = dayBarSprite.getPosition().x + 107;
	}
	sunSprite.move((sunSpriteDesiredLocation - sunSprite.getPosition()) * elapsed.asSeconds() * 4.0f);

	fastButton.setTextureRect(sf::IntRect(state->timeSpeed == 1 ? 0 : 12, 0, 12, 10));

	dayText.setText("Day " + std::to_string(state->day));
	lightText.setText(std::to_string(int(state->light)) + "/" + std::to_string(state->maxLight));
	waterText.setText(std::to_string(int(state->water)) + "/" + std::to_string(state->maxWater));
	nutrientsText.setText(std::to_string(int(state->nutrients)) + "/" + std::to_string(state->maxNutrients));

	updateDeltaTexts(elapsed);

	if (state->selectedObject) {
		infoPane.move((sf::Vector2f(240 - infoPane.getTexture()->getSize().x, 135 - infoPane.getTexture()->getSize().y) - infoPane.getPosition()) * elapsed.asSeconds() * 7.0f);
	}
	else {
		infoPane.move((sf::Vector2f(240, 135 - infoPane.getTexture()->getSize().y) - infoPane.getPosition()) * elapsed.asSeconds() * 7.0f);
	}
	infoTitle.setPosition(infoPane.getPosition() + sf::Vector2f(4, 4));
	infoDescription.setPosition(infoPane.getPosition() + sf::Vector2f(2, 18));
	upgrade1Text.setPosition(infoPane.getPosition() + sf::Vector2f(4, 72));
	upgrade2Text.setPosition(infoPane.getPosition() + sf::Vector2f(4, 86));
	upgrade3Text.setPosition(infoPane.getPosition() + sf::Vector2f(4, 100));
	costPane.setPosition(infoPane.getPosition() + sf::Vector2f(89, 38));
	for (int i = 0; i < stats.size(); i++) {
		if (i < 3) {
			stats[i].setPosition(infoPane.getPosition() + sf::Vector2f(12, 38 + 10 * i));
		}
		else {
			stats[i].setPosition(infoPane.getPosition() + sf::Vector2f(56, 38 + 10 * (i - 3)));
		}
	}
	
	lastLight = state->light;
	lastWater = state->water;
	lastNutrients = state->nutrients;
}

void Hud::populateInfo(std::shared_ptr<GridObject> object) {
	upgrade1Text.setText("");
	upgrade2Text.setText("");
	upgrade3Text.setText("");
	if (std::dynamic_pointer_cast<Tree>(object)) {
		infoPane.setTexture(state->loadTexture("Resource/Image/InfoPane.png"));
		std::shared_ptr<Tree> treeObject = std::dynamic_pointer_cast<Tree>(object);
		infoTitle.setText(treeObject->getType());
		infoDescription.setText(getTreeDescription(treeObject->getType()));
		loadStats(treeObject);
		if (getTreeUpgradeOptions(treeObject->getType()).size() >= 1) {
			if (state->isResearched(getTreeUpgradeOptions(treeObject->getType())[0])) {
				upgrade1Text.setText(getTreeUpgradeOptions(treeObject->getType())[0]);
			}
			else {
				upgrade1Text.setText("???");
			}
		}
		if (getTreeUpgradeOptions(treeObject->getType()).size() >= 2) {
			if (state->isResearched(getTreeUpgradeOptions(treeObject->getType())[1])) {
				upgrade2Text.setText(getTreeUpgradeOptions(treeObject->getType())[1]);
			}
			else {
				upgrade2Text.setText("???");
			}
		}
		if (getTreeUpgradeOptions(treeObject->getType()).size() >= 3) {
			if (state->isResearched(getTreeUpgradeOptions(treeObject->getType())[2])) {
				upgrade3Text.setText(getTreeUpgradeOptions(treeObject->getType())[2]);
			}
			else {
				upgrade3Text.setText("???");
			}
		}
	}
	else if (std::dynamic_pointer_cast<Ruin>(object)) {
		std::shared_ptr<Ruin> ruinObject = std::dynamic_pointer_cast<Ruin>(object);
		infoPane.setTexture(state->loadTexture("Resource/Image/ResearchPane.png"));
		if (ruinObject->getType() == "Large") {
			infoTitle.setText(ruinObject->getSubType() + " Tower");
			if (infoTitle.getText() == "Nutrients Tower") {
				infoTitle.setText("Nutrient Tower");
			}
			infoDescription.setText("A Monument that\ndesires " + ruinObject->getSubType() + ".\n\nSacrifice enough\nresources to all\ntowers to win\nthe game.");
		}
		else {
			infoTitle.setText("Garden Shrine");
			infoDescription.setText("A shrine that\nteaches how to\ngrow the\n" + ruinObject->getSubType() + "\nplant when given\nenough light.");
		}
		upgrade3Text.setText(std::to_string(ruinObject->charge) + "/" + std::to_string(ruinObject->maxCharge));
		stats.clear();
	}
	else {
		infoTitle.setText("Unknown");
		infoDescription.setText("");
		stats.clear();
	}
}

bool Hud::isCursorOnHud() const {
	sf::Vector2f cursorLocation = state->getCursorLocation();
	if (state->selectedObject && cursorLocation.x >= 120 && cursorLocation.y >= 25) {
		return true;
	}
	else if (cursorLocation.x < 50 && cursorLocation.y < 48) {
		return true;
	}
	else if (fastButton.getGlobalBounds().contains(cursorLocation)) {
		return true;
	}
	else if (dayBarSprite.getGlobalBounds().contains(cursorLocation)) {
		return true;
	}
	else {
		return false;
	}
}

bool Hud::isCursorOnFastButton() {
	sf::FloatRect fastButton(50, 2, 8, 6);
	return fastButton.contains(state->getCursorLocation());
}

void Hud::chooseUpgrade(int selection) {
	if (state->isOwnedTree(state->selectedObject)) {
		std::string newType = "";
		if (selection == 0) {
			newType = upgrade1Text.getText();
		}
		else if (selection == 1) {
			newType = upgrade2Text.getText();
		}
		else if (selection == 2) {
			newType = upgrade3Text.getText();
		}

		if (newType != "" && newType != "???") {
			if (state->selectedObject && std::dynamic_pointer_cast<Tree>(state->selectedObject)) {
				if (state->light >= getTreeUpgradeCost(newType).light && state->nutrients >= getTreeUpgradeCost(newType).nutrients) {
					state->spendLight(getTreeUpgradeCost(newType).light, state->selectedObject->getPosition());
					state->spendNutrients(getTreeUpgradeCost(newType).nutrients, state->selectedObject->getPosition());
					std::dynamic_pointer_cast<Tree>(state->selectedObject)->setType(newType);
					populateInfo(state->selectedObject);
				}
			}
		}
	}
	else if (std::dynamic_pointer_cast<Ruin>(state->selectedObject)) {
		if (selection == 2) {
			std::shared_ptr<Ruin> ruinObject = std::dynamic_pointer_cast<Ruin>(state->selectedObject);
			if (ruinObject->getSubType() == "Water") {
				int amountSpent = std::min(ruinObject->maxCharge - ruinObject->charge, (int)state->water);
				ruinObject->charge += amountSpent;
				state->spendWater(amountSpent, ruinObject->getPosition());
			}
			else if (ruinObject->getSubType() == "Nutrients") {
				int amountSpent = std::min(ruinObject->maxCharge - ruinObject->charge, (int)state->nutrients);
				ruinObject->charge += amountSpent;
				state->spendNutrients(amountSpent, ruinObject->getPosition());
			}
			else {
				int amountSpent = std::min(ruinObject->maxCharge - ruinObject->charge, (int)state->light);
				ruinObject->charge += amountSpent;
				state->spendLight(amountSpent, ruinObject->getPosition());
			}
			populateInfo(ruinObject);
		}
	}
}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(resourcesHud);
	target.draw(dayText);
	target.draw(lightText);
	target.draw(waterText);
	target.draw(nutrientsText);

	target.draw(fastButton);

	target.draw(dayBarBg);
	target.draw(dayBar);
	target.draw(sunSprite);
	target.draw(dayBarSprite);

	target.draw(infoPane);
	target.draw(infoTitle);
	target.draw(infoDescription);
	for (const BitmapText &text : stats) {
		target.draw(text);
	}

	target.draw(upgrade1Text);
	target.draw(upgrade2Text);
	target.draw(upgrade3Text);
	if (state->isOwnedTree(state->selectedObject)) {
		sf::Sprite noUpgrade(state->loadTexture("Resource/Image/NoUpgrade.png"));
		if (upgrade1Text.text == "") {
			noUpgrade.setPosition(infoPane.getPosition() + sf::Vector2f(2, 70));
			target.draw(noUpgrade);
		}
		if (upgrade2Text.text == "") {
			noUpgrade.setPosition(infoPane.getPosition() + sf::Vector2f(2, 84));
			target.draw(noUpgrade);
		}
		if (upgrade3Text.text == "") {
			noUpgrade.setPosition(infoPane.getPosition() + sf::Vector2f(2, 98));
			target.draw(noUpgrade);
		}
	}

	if (state->isOwnedTree(state->selectedObject)) {
		sf::IntRect upgrade1Button(240 - 14, 135 - 42, 12, 12);
		sf::IntRect upgrade2Button(240 - 14, 135 - 28, 12, 12);
		sf::IntRect upgrade3Button(240 - 14, 135 - 14, 12, 12);
		if (upgrade1Button.contains(state->getCursorLocation().x, state->getCursorLocation().y)) {
			if (upgrade1Text.getText() != "" && upgrade1Text.getText() != "???") {
				target.draw(costPane);
				renderCost(target, getTreeUpgradeCost(upgrade1Text.getText()).light, getTreeUpgradeCost(upgrade1Text.getText()).nutrients);
			}
		}
		else if (upgrade2Button.contains(state->getCursorLocation().x, state->getCursorLocation().y)) {
			if (upgrade2Text.getText() != "" && upgrade2Text.getText() != "???") {
				target.draw(costPane);
				renderCost(target, getTreeUpgradeCost(upgrade2Text.getText()).light, getTreeUpgradeCost(upgrade2Text.getText()).nutrients);
			}
		}
		else if (upgrade3Button.contains(state->getCursorLocation().x, state->getCursorLocation().y)) {
			if (upgrade3Text.getText() != "" && upgrade3Text.getText() != "???") {
				target.draw(costPane);
				renderCost(target, getTreeUpgradeCost(upgrade3Text.getText()).light, getTreeUpgradeCost(upgrade3Text.getText()).nutrients);
			}
		}
	}

	target.draw(lightDeltaText);
	target.draw(waterDeltaText);
	target.draw(nutrientsDeltaText);
}

void Hud::loadStats(std::shared_ptr<Tree> tree) {
	stats.clear();
	BitmapText statText;
	statText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	statText.setColor(sf::Color::White);

	statText.setText(std::to_string((int)tree->stats.lightIncome));
	stats.push_back(statText);
	statText.setText(std::to_string((int)tree->stats.range));
	stats.push_back(statText);
	std::string attackRate = std::to_string(tree->stats.attackRate);
	if (attackRate.find('.')) {
		attackRate = attackRate.substr(0, attackRate.find('.') + 3);
	}
	statText.setText(attackRate);
	stats.push_back(statText);

	statText.setColor(state->getResourceColor("Light"));
	statText.setText(std::to_string((int)tree->stats.maxLight));
	stats.push_back(statText);
	statText.setColor(state->getResourceColor("Water"));
	statText.setText(std::to_string((int)tree->stats.maxWater));
	stats.push_back(statText);
	statText.setColor(state->getResourceColor("Nutrients"));
	statText.setText(std::to_string((int)tree->stats.maxNutrients));
	stats.push_back(statText);
}

void Hud::renderCost(sf::RenderTarget &target, int light, int nutrients) const {
	BitmapText costText;
	costText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	costText.setColor(state->getResourceColor("Light"));
	costText.setText(std::to_string(light));
	costText.setPosition(costPane.getPosition() + sf::Vector2f(12, 12));
	target.draw(costText);
	costText.setColor(state->getResourceColor("Nutrients"));
	costText.setText(std::to_string(nutrients));
	costText.setPosition(costPane.getPosition() + sf::Vector2f(12, 22));
	target.draw(costText);
}

void Hud::updateDeltaTexts(sf::Time elapsed) {
	if (lightDeltaText.getPosition().x > 0) {
		lightDeltaText.move((sf::Vector2f(53, 18) - lightDeltaText.getPosition()) * elapsed.asSeconds() * 2.0f);
		if (lightDeltaText.getPosition().x > 52) {
			lightDeltaText.setPosition(-100, -100);
		}
	}
	if ((int)state->light != (int)lastLight) {
		int delta = (int)state->light - (int)lastLight;
		lightDeltaText.setText((delta > 0 ? "+" : "") + std::to_string((int)state->light - (int)lastLight));
		lightDeltaText.setPosition(40, 18);
	}

	if (waterDeltaText.getPosition().x > 0) {
		waterDeltaText.move((sf::Vector2f(53, 28) - waterDeltaText.getPosition()) * elapsed.asSeconds() * 2.0f);
		if (waterDeltaText.getPosition().x > 52) {
			waterDeltaText.setPosition(-100, -100);
		}
	}
	if ((int)state->water != (int)lastWater) {
		int delta = (int)state->water - (int)lastWater;
		waterDeltaText.setText((delta > 0 ? "+" : "") + std::to_string((int)state->water - (int)lastWater));
		waterDeltaText.setPosition(40, 28);
	}

	if (nutrientsDeltaText.getPosition().x > 0) {
		nutrientsDeltaText.move((sf::Vector2f(53, 38) - nutrientsDeltaText.getPosition()) * elapsed.asSeconds() * 2.0f);
		if (nutrientsDeltaText.getPosition().x > 52) {
			nutrientsDeltaText.setPosition(-100, -100);
		}
	}
	if ((int)state->nutrients != (int)lastNutrients) {
		int delta = (int)state->nutrients - (int)lastNutrients;
		nutrientsDeltaText.setText((delta > 0 ? "+" : "") + std::to_string((int)state->nutrients - (int)lastNutrients));
		nutrientsDeltaText.setPosition(40, 38);
	}
}

#pragma once

#include "Object.h"
#include "BitmapText.h"
#include "GridObject.h"
#include "Tree.h"
#include <SFML/Graphics.hpp>

class Hud : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

	void populateInfo(std::shared_ptr<GridObject> object);
	bool isCursorOnHud() const;
	bool isCursorOnFastButton();
	void chooseUpgrade(int selection);

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void loadStats(std::shared_ptr<Tree> tree);
	void renderCost(sf::RenderTarget &target, int light, int nutrients) const;

	void updateDeltaTexts(sf::Time elapsed);

	// Internal data
	float lastLight;
	float lastWater;
	float lastNutrients;

	// Resources
	sf::Sprite dayBarSprite;
	sf::RectangleShape dayBar;
	sf::Sprite dayBarBg;
	sf::Sprite sunSprite;

	sf::Sprite fastButton;

	sf::Sprite infoPane;
	BitmapText infoTitle;
	BitmapText infoDescription;
	std::vector<BitmapText> stats;
	BitmapText upgrade1Text;
	BitmapText upgrade2Text;
	BitmapText upgrade3Text;
	sf::Sprite costPane;

	sf::Sprite resourcesHud;
	BitmapText dayText;
	BitmapText lightText;
	BitmapText lightDeltaText;
	BitmapText waterText;
	BitmapText waterDeltaText;
	BitmapText nutrientsText;
	BitmapText nutrientsDeltaText;
};


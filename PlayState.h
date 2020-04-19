#pragma once

#include "State.h"
#include "BitmapText.h"
#include "Fairy.h"
#include "Tree.h"
#include "Hud.h"
#include "GridTile.h"
#include <SFML/Audio.hpp>
#include <memory>

struct Particle {
	enum ParticleType {
		dot,
		minus,
		plus
	} type = dot;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color color;
	float lifetime = 0.7;
	bool onHud = false;
};

class PlayState : public State {
public:
	PlayState();
	~PlayState();

	virtual void init();
	virtual void gotEvent(sf::Event event);
	virtual void update(sf::Time elapsed);
	virtual void render(sf::RenderWindow &window);

	sf::Vector2f cameraPosition;

	std::string getTimeOfDay();
	sf::Color getResourceColor(std::string resource);

	void gainLight(float gained, int x = -1, int y = -1);
	bool spendLight(float spent, int x = -1, int y = -1);
	void gainWater(float gained, int x = -1, int y = -1);
	bool spendWater(float spent, int x = -1, int y = -1);
	void gainNutrients(float gained, int x = -1, int y = -1);
	bool spendNutrients(float spent, int x = -1, int y = -1);

	void createParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, Particle::ParticleType type = Particle::ParticleType::dot, bool onHud = false);
	void updateParticles(sf::Time elapsed);

	// Game Stats
	float secondsPerDay = 10;

	// Game data
	sf::Vector2i worldSize;
	std::vector<std::shared_ptr<GridTile>> tileGrid;
	std::vector<std::shared_ptr<GridObject>> objectGrid;

	int day = 1;
	int hour = 2;
	float time;

	float light = 0;
	int maxLight = 15;
	float water = 10;
	int maxWater = 10;
	float nutrients = 10;
	int maxNutrients = 20;

private:
	void buildWorld(int worldWidth, int worldHeight);

	std::shared_ptr<GridTile> getGridTile(int x, int y);
	void setGridTile(int x, int y, std::string newType);
	std::shared_ptr<GridObject> getGridObject(int x, int y);
	void setGridObject(int x, int y, std::shared_ptr<GridObject> newObject);

	sf::Vector2i worldLocationToGrid(sf::Vector2f location);
	sf::Vector2f screenLocationToWorld(sf::Vector2f location);
	sf::Vector2f getCursorLocation();
	sf::Vector2i getCursorGridLocation();

	void updateOverlays();

	// Resources
	BitmapText testText;
	Fairy player;
	Hud hud;
	sf::Sprite cursor;

	std::vector<Particle> particles;

	sf::RectangleShape transitionOverlay;
	sf::RectangleShape nightOverlay;

	sf::Music dayMusic;
	sf::Music nightMusic;
};


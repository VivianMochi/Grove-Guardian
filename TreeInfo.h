#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct UpgradeCost {
	UpgradeCost(int light = 0, int nutrients = 0, int water = 0) : light(light), water(water), nutrients(nutrients) {}
	int light;
	int water;
	int nutrients;
};

struct TreeStats {
	int maxLight = 0;
	int maxWater = 0;
	int maxNutrients = 0;
	int lightIncome = 0;
	float range = 0;
	float attackRate = 0;
	int waterMultiplier = 1;
	int nutrientsMultiplier = 1;
	int waterIncome = 0;
	int nutrientsIncome = 0;
	bool buff = false;
	sf::Color color;
};

std::vector<std::string> getTreeUpgradeOptions(std::string type);
UpgradeCost getTreeUpgradeCost(std::string type);
std::string getTreeDescription(std::string type);
TreeStats getTreeStats(std::string type);
int getTreeTier(std::string type);
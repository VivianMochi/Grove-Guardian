#pragma once

#include <vector>
#include <string>

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
};

std::vector<std::string> getTreeUpgradeOptions(std::string type);
UpgradeCost getTreeUpgradeCost(std::string type);
std::string getTreeDescription(std::string type);
TreeStats getTreeStats(std::string type);
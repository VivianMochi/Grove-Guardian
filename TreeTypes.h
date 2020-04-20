#pragma once

#include <vector>
#include <string>

struct UpgradeCost {
	UpgradeCost(int light = 0, int nutrients = 0, int water = 0) : light(light), water(water), nutrients(nutrients) {}
	int light;
	int water;
	int nutrients;
};

std::vector<std::string> getUpgradeOptions(std::string type) {
	if (type == "Root") {
		return { "Sapling", "Shrub", "Weeds" };
	}
	else if (type == "Sapling") {
		return { "Tree", "Willow" };
	}
	else if (type == "Shrub") {
		return { "Cactus", "Soybean" };
	}
	else if (type == "Weeds") {
		return { "Waterlily", "Glowshroom" };
	}
	else if (type == "Mother Tree") {
		return { "Grand Mother" };
	}
	else {
		return {};
	}
}

UpgradeCost getUpgradeCost(std::string type) {
	if (type == "Sapling") {
		return UpgradeCost(10, 2);
	}
	else if (type == "Shrub") {
		return UpgradeCost(5, 4);
	}
	else if (type == "Weeds") {
		return UpgradeCost(2, 0);
	}
	else if (type == "Tree") {
		return UpgradeCost(30, 10);
	}
	else if (type == "Willow") {
		return UpgradeCost(30, 10);
	}
	else if (type == "Cactus") {
		return UpgradeCost(30, 10);
	}
	else if (type == "Soybean") {
		return UpgradeCost(10, 2);
	}
	else if (type == "Waterlily") {
		return UpgradeCost(10, 2);
	}
	else if (type == "Glowshroom") {
		return UpgradeCost(10, 2);
	}
	else if (type == "Grand Mother") {
		return UpgradeCost(30, 50);
	}
	else {
		return UpgradeCost();
	}
}

std::string getDescription(std::string type) {
	if (type == "Root") {
		return "I am root.\n";
	}
	else if (type == "Sapling") {
		return "A young sprout.\nVery versatile.";
	}
	else if (type == "Shrub") {
		return "A little shrub.\nStores light.";
	}
	else if (type == "Weeds") {
		return "Cheap but holds\nnutrients.";
	}
	else if (type == "Tree") {
		return "Ah, a tree.\nHow lovely.";
	}
	else if (type == "Willow") {
		return "Double attack\nrange on water.";
	}
	else if (type == "Cactus") {
		return "Holds water.\nAlso deadly.";
	}
	else if (type == "Soybean") {
		return "Makes nutrients\nby itself.";
	}
	else if (type == "Waterlily") {
		return "Quadruple water\nintake.";
	}
	else if (type == "Glowshroom") {
		return "Makes light at\nNight. Cool!";
	}
	if (type == "Mother Tree") {
		return "The grove's heart.\nKeep it alive.";
	}
	else if (type == "Grand Mother") {
		return "An Old Mom.\nHealthy as ever.";
	}
	else {
		return "";
	}
}
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
		return { "Sapling" };
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
	else if (type == "Grand Mother") {
		return UpgradeCost(30, 50);
	}
	else {
		return UpgradeCost();
	}
}

std::string getDescription(std::string type) {
	if (type == "Mother Tree") {
		return "The grove's heart.\nKeep it alive.";
	}
	else if (type == "Grand Mother") {
		return "An Old Mom.\nHealthy as ever.";
	}
	else if (type == "Root") {
		return "I am root.\n";
	}
	else if (type == "Sapling") {
		return "A young sprout.\nVery versatile.";
	}
	else {
		return "";
	}
}
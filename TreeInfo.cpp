#include "TreeInfo.h"

std::vector<std::string> getTreeUpgradeOptions(std::string type) {
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
	else if (type == "Seaweed") {
		return { "Kelp", "Seagrass", "Coral"};
	}
	else if (type == "Mother Tree") {
		return { "Grand Mother" };
	}
	else {
		return {};
	}
}

UpgradeCost getTreeUpgradeCost(std::string type) {
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
		return UpgradeCost(20, 10);
	}
	else if (type == "Willow") {
		return UpgradeCost(30, 15);
	}
	else if (type == "Cactus") {
		return UpgradeCost(15, 20);
	}
	else if (type == "Soybean") {
		return UpgradeCost(10, 30);
	}
	else if (type == "Waterlily") {
		return UpgradeCost(10, 2);
	}
	else if (type == "Glowshroom") {
		return UpgradeCost(15, 10);
	}
	else if (type == "Grand Mother") {
		return UpgradeCost(50, 50);
	}
	else {
		return UpgradeCost(99, 99);
	}
}

std::string getTreeDescription(std::string type) {
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
	else if (type == "Seaweed") {
		return "50% sea.\n50% weed.";
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

TreeStats getTreeStats(std::string type) {
	if (type == "Sapling") {
		return TreeStats{ 2, 1, 2, 1, 3, 0.25 };
	}
	else if (type == "Shrub") {
		return TreeStats{ 5, 0, 0, 0, 0, 0 };
	}
	else if (type == "Weeds") {
		return TreeStats{ 0, 0, 2, 0, 0, 0 };
	}
	else if (type == "Tree") {
		return TreeStats{ 6, 3, 4, 2, 4, 0.25 };
	}
	else if (type == "Willow") {
		return TreeStats{ 5, 4, 3, 1, 5, 0.5 };
	}
	else if (type == "Cactus") {
		return TreeStats{ 0, 8, 0, 0, 6, 1 };
	}
	else if (type == "Soybean") {
		return TreeStats{ 0, 0, 2, 0, 4, 0.25 };
	}
	else if (type == "Waterlily") {
		return TreeStats{ 1, 4, 1, 1, 0, 0 };
	}
	else if (type == "Glowshroom") {
		return TreeStats{ 0, 0, 5, 3, 4, 0.25 };
	}
	else if (type == "Mother Tree") {
		return TreeStats{ 15, 10, 20, 3, 5, 0.5 };
	}
	else if (type == "Grand Mother") {
		return TreeStats{ 50, 50, 50, 5, 10, 1 };
	}
	else {
		return TreeStats();
	}
}

int getTreeTier(std::string type) {
	if (type == "Root") {
		return 0;
	}
	std::vector<std::string> tier1 = getTreeUpgradeOptions("Root");
	std::vector<std::string> tier2;
	for (std::string tree : tier1) {
		if (type == tree) {
			return 1;
		}
		std::vector<std::string> options = getTreeUpgradeOptions(tree);
		tier2.insert(tier2.end(), options.begin(), options.end());
	}
	tier2.push_back("Seaweed");
	for (std::string tree : tier2) {
		if (type == tree) {
			return 2;
		}
	}
	return 3;
}

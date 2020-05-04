#include "TreeInfo.h"

std::vector<std::string> getTreeUpgradeOptions(std::string type) {
	if (type == "Root") {
		return { "Sapling", "Shrub", "Weeds" };
	}
	else if (type == "Sapling") {
		return { "Oak", "Birch", "Willow" };
	}
	else if (type == "Oak") {
		return { "Red Oak", "Holly Oak" };
	}
	else if (type == "Birch") {
		return { "Sweet Birch", "Bamboo" };
	}
	else if (type == "Willow") {
		return { "TODO", "TODO" };
	}
	else if (type == "Shrub") {
		return { "Soybean", "Cactus", "TODO" };
	}
	else if (type == "Soybean") {
		return { "TODO", "TODO" };
	}
	else if (type == "Cactus") {
		return { "TODO", "TODO" };
	}
	else if (type == "Weeds") {
		return { "Waterlily", "Aloe", "Mushroom" };
	}
	else if (type == "Waterlily") {
		return { "Mangrove", "Moss" };
	}
	else if (type == "Aloe") {
		return { "Venus Fly Trap", "TODO" };
	}
	else if (type == "Mushroom") {
		return { "Megashroom", "Glowshroom"};
	}
	else if (type == "Seaweed") {
		return { "Kelp", "Seagrass", "Coral"};
	}
	else if (type == "Kelp") {
		return { "Red Algae", "TODO" };
	}
	else if (type == "Seagrass") {
		return { "Sargassum", "TODO" };
	}
	else if (type == "Coral") {
		return { "Sea Sponge", "TODO" };
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
		return UpgradeCost(8, 2);
	}
	else if (type == "Shrub") {
		return UpgradeCost(5, 4);
	}
	else if (type == "Weeds") {
		return UpgradeCost(2, 0);
	}
	else if (type == "Oak") {
		return UpgradeCost(15, 8);
	}
	else if (type == "Willow") {
		return UpgradeCost(25, 10);
	}
	else if (type == "Cactus") {
		return UpgradeCost(20, 15);
	}
	else if (type == "Soybean") {
		return UpgradeCost(10, 25);
	}
	else if (type == "Waterlily") {
		return UpgradeCost(10, 2);
	}
	else if (type == "Mushroom") {
		return UpgradeCost(5, 5);
	}
	else if (type == "Megashroom") {
		return UpgradeCost(15, 10);
	}
	else if (type == "Glowshroom") {
		return UpgradeCost(15, 10);
	}
	else if (type == "Kelp") {
		return UpgradeCost(15, 6);
	}
	else if (type == "Seagrass") {
		return UpgradeCost(4, 2);
	}
	else if (type == "Coral") {
		return UpgradeCost(15, 10);
	}
	else if (type == "Grand Mother") {
		return UpgradeCost(50, 30);
	}
	else {
		return UpgradeCost();
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
	else if (type == "Oak") {
		return "Ah, an oak tree.\nHow lovely.";
	}
	else if (type == "Red Oak") {
		return "TODO";
	}
	else if (type == "Holly Oak") {
		return "TODO";
	}
	else if (type == "Willow") {
		return "Double attack\nrange on water.";
	}
	else if (type == "Cactus") {
		return "Holds water.\nAlso deadly.";
	}
	else if (type == "Soybean") {
		return "Makes nutrients\nanywhere.";
	}
	else if (type == "Waterlily") {
		return "Triple water\nintake.";
	}
	else if (type == "Mushroom") {
		return "Extracts triple\nnutrients.";
	}
	else if (type == "Megashroom") {
		return "Emits spores that\nslow spirits.";
	}
	else if (type == "Glowshroom") {
		return "Makes light at\nNight. Cool!";
	}
	else if (type == "Seaweed") {
		return "50% sea.\n50% weed.";
	}
	else if (type == "Kelp") {
		return "It's just Kelp.";
	}
	else if (type == "Seagrass") {
		return "Easy to grow.\nGathers light.";
	}
	else if (type == "Coral") {
		return "Beautiful! Stores\na lot of stuff.";
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
		TreeStats stats{ 2, 1, 2, 1, 3, 0.25 };
		stats.color = sf::Color(55, 130, 68);
		return stats;
	}
	else if (type == "Shrub") {
		TreeStats stats{ 5, 0, 0, 0, 0, 0 };
		stats.color = sf::Color(55, 130, 68);
		return stats;
	}
	else if (type == "Weeds") {
		return TreeStats{ 0, 0, 2, 0, 0, 0 };
	}
	else if (type == "Oak") {
		TreeStats stats{ 6, 3, 4, 2, 4, 0.25 };
		stats.color = sf::Color(55, 130, 68);
		return stats;
	}
	else if (type == "Red Oak") {
		TreeStats stats{ 6, 3, 4, 2, 4, 0.25 };
		stats.color = sf::Color(233, 54, 32);
		return stats;
	}
	else if (type == "Holly Oak") {
		TreeStats stats{ 6, 3, 4, 2, 4, 0.25 };
		stats.color = sf::Color(162, 169, 133);
		return stats;
	}
	else if (type == "Birch") {
		TreeStats stats{ 6, 3, 4, 2, 4, 0.25 };
		stats.color = sf::Color(55, 130, 68);
		return stats;
	}
	else if (type == "Sweet Birch") {
		TreeStats stats{ 6, 3, 4, 2, 4, 0.25 };
		stats.color = sf::Color(198, 155, 55);
		return stats;
	}
	else if (type == "Willow") {
		return TreeStats{ 5, 4, 3, 1, 5, 0.5 };
	}
	else if (type == "Cactus") {
		return TreeStats{ 0, 8, 0, 0, 6, 1 };
	}
	else if (type == "Soybean") {
		return TreeStats{ 0, 0, 2, 0, 4, 0.25, 1, 1, 0, 1};
	}
	else if (type == "Waterlily") {
		return TreeStats{ 1, 4, 1, 1, 0, 0, 3 };
	}
	else if (type == "Mushroom") {
		return TreeStats{ 0, 0, 0, 0, 0, 0, 1, 3 };
	}
	else if (type == "Megashroom") {
		return TreeStats{ 0, 0, 5, 3, 6, 0 };
	}
	else if (type == "Glowshroom") {
		return TreeStats{ 0, 0, 5, 3, 4, 0.25 };
	}
	else if (type == "Kelp") {
		return TreeStats{ 0, 0, 0, 0, 5, 0.5 };
	}
	else if (type == "Seagrass") {
		return TreeStats{ 0, 0, 0, 1, 0, 0 };
	}
	else if (type == "Coral") {
		return TreeStats{ 5, 5, 5, 0, 0, 0 };
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

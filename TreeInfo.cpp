#include "TreeInfo.h"

// This is a really ugly file. I'm so sorry.
// Next update, I'm going to offload these stats into text files

MetaObject getTreeMetaObject(std::string type) {
	MetaObject object;
	if (type == "Root") {
		object.description = "I am root.\n";
		object.upgrades = { "Sapling", "Shrub", "Weeds" };
	}
	else if (type == "Sapling") {
		object.description = "A young sprout.\nVery versatile.";
		object.stats = { 1, 1, 1, 1, 3, 0.25 };
		object.stats.color = sf::Color(55, 130, 68);
		object.cost = UpgradeCost(4, 2);
		object.upgrades = { "Oak", "Birch", "Mangrove" };
	}
	else if (type == "Shrub") {
		object.description = "A little shrub.\nStores light.";
		object.stats = { 4, 0, 0, 0, 0, 0 };
		object.stats.color = sf::Color(55, 130, 68);
		object.cost = UpgradeCost(2, 4);
		object.upgrades = { "Soybean", "Succulent", "Ivy" };
	}
	else if (type == "Weeds") {
		object.description = "Cheap but holds\nnutrients.";
		object.stats = { 0, 0, 2, 0, 0, 0 };
		object.cost = UpgradeCost(2, 0);
		object.upgrades = { "Waterlily", "Venus Fly Trap", "Mushroom" };
	}
	else if (type == "Oak") {
		object.description = "Ah, an oak tree.\nHow lovely.";
		object.stats = { 4, 4, 4, 2, 4, 0.5 };
		object.stats.color = sf::Color(55, 130, 68);
		object.cost = UpgradeCost(10, 8);
		object.upgrades = { "Red Oak", "Holly Oak" };
	}
	else if (type == "Red Oak") {
		object.description = "A short range\nrapid fire oak.";
		object.stats = { 6, 6, 6, 2, 4, 2 };
		object.stats.color = sf::Color(233, 54, 32);
		object.cost = UpgradeCost(15, 10);
	}
	else if (type == "Holly Oak") {
		object.description = "A long range\nsniper oak.";
		object.stats = { 6, 6, 6, 2, 8, 1 };
		object.stats.color = sf::Color(162, 169, 133);
		object.cost = UpgradeCost(15, 10);
	}
	else if (type == "Birch") {
		object.description = "Fantastic at\ngathering light.";
		object.stats = { 4, 2, 2, 4, 4, 0.25 };
		object.stats.color = sf::Color(55, 130, 68);
		object.cost = UpgradeCost(15, 3);
		object.upgrades = { "Sweet Birch", "Bamboo" };
	}
	else if (type == "Sweet Birch") {
		object.description = "Double light\non nutrients.";
		object.stats = { 8, 4, 4, 4, 4, 0.25 };
		object.stats.color = sf::Color(198, 155, 55);
		object.cost = UpgradeCost(20, 15);
	}
	else if (type == "Bamboo") {
		object.description = "Range is equal to\ntotal light / 10.";
		object.stats = { -6, 4, 4, 0, 1, 1 };
		object.stats.color = sf::Color(127, 177, 52);
		object.cost = UpgradeCost(25, 20);
	}
	else if (type == "Mangrove") {
		object.description = "A small\nmarsh tree.";
		object.stats = { 2, 4, 2, 1, 5, 0.5 };
		object.stats.color = sf::Color(120, 151, 66);
		object.cost = UpgradeCost(15, 8);
		object.upgrades = { "Willow" };
	}
	else if (type == "Willow") {
		object.description = "Double attack\nrange on water.";
		object.stats = { 4, 8, 4, 1, 5, 2 };
		object.stats.color = sf::Color(120, 151, 66);
		object.cost = UpgradeCost(20, 10);
	}
	else if (type == "Soybean") {
		object.description = "Makes nutrients\nanywhere.";
		object.stats = { 0, 0, 2, 0, 4, 0.25, 1, 1, 0, 1 };
		object.cost = UpgradeCost(15, 10);
		object.upgrades = { "Corn", "Blackberry" };
	}
	else if (type == "Corn") {
		object.description = "Better nutrient\nmaking ability.";
		object.stats = { 0, 0, 4, 1, 4, 0.5, 1, 1, 0, 2 };
		object.cost = UpgradeCost(25, 25);
	}
	else if (type == "Blackberry") {
		object.description = "Gain 10% nutrient\ninterest per day.";
		object.stats = { 0, 0, 10 };
		object.cost = UpgradeCost(20, 15);
	}
	else if (type == "Succulent") {
		object.description = "A cute little\nplant. Adorable.";
		object.stats = { 0, 4, 0, 1, 0, 0 };
		object.cost = UpgradeCost(10, 10);
		object.upgrades = { "Cactus", "Aloe" };
	}
	else if (type == "Cactus") {
		object.description = "Holds water.\nAlso deadly.";
		object.stats = { 0, 8, 0, 0, 6, 4 };
		object.cost = UpgradeCost(15, 15);
	}
	else if (type == "Aloe") {
		object.description = "Uses light to\nprotect plants.";
		object.stats = { 0, 4, 0, 0, 4, 0 };
		object.stats.buff = true;
		object.cost = UpgradeCost(20, 15);
	}
	else if (type == "Ivy") {
		object.description = "Ivy, ready to\nstart spreading.";
		object.stats = { 0, 0, 0 };
		object.cost = UpgradeCost(20, 15);
		object.upgrades = { "Creeping Ivy", "Poison Ivy" };
	}
	else if (type == "Creeping Ivy") {
		object.description = "Occasionally\npropagates.";
		object.cost = UpgradeCost(5, 5);
		object.upgrades = { "Root", "Poison Ivy" };
	}
	else if (type == "Poison Ivy") {
		object.description = "A poisonous ivy.\nDoesn't spread.";
		object.stats = { 0, 0, 0, 0, 5, 0.25 };
		object.cost = UpgradeCost(5, 5);
		object.upgrades = { "Root" };
	}
	else if (type == "Waterlily") {
		object.description = "Triple water\nintake.";
		object.stats = { 0, 2, 0, 1, 0, 0, 3 };
		object.cost = UpgradeCost(10, 2);
		object.upgrades = { "Cattail", "Moss" };
	}
	else if (type == "Cattail") {
		object.description = "Makes water\non shoreline.";
		object.stats = { 0, 4, 0 };
		object.cost = UpgradeCost(15, 10);
	}
	else if (type == "Moss") {
		object.description = "Balances all\nresources daily.";
		object.cost = UpgradeCost(30, 20);
	}
	else if (type == "Venus Fly Trap") {
		object.description = "Loves to eat\nspirits.";
		object.stats = { 0, 0, 0, 0, 5, 0.25 };
		object.cost = UpgradeCost(10, 5);
		object.upgrades = { "Pitcher Plant", "Rafflesia" };
	}
	else if (type == "Pitcher Plant") {
		object.description = "Gains nutrients\nOn kill.";
		object.stats = { 0, 0, 0, 0, 5, 2};
		object.cost = UpgradeCost(20, 10);
	}
	else if (type == "Rafflesia") {
		object.description = "Mass storage.\nAlso scary.";
		object.stats = { 14, 14, 14 };
		object.cost = UpgradeCost(15, 10);
	}
	else if (type == "Mushroom") {
		object.description = "Extracts triple\nnutrients.";
		object.stats = { 0, 0, 0, 0, 0, 0, 1, 3 };
		object.cost = UpgradeCost(5, 5);
		object.upgrades = { "Megashroom", "Glowshroom" };
	}
	else if (type == "Megashroom") {
		object.description = "Emits spores that\nslow spirits.";
		object.stats = { 0, 0, 0, 0, 6, 0 };
		object.stats.buff = true;
		object.cost = UpgradeCost(10, 10);
	}
	else if (type == "Glowshroom") {
		object.description = "Makes light at\nNight. Cool!";
		object.stats = { 0, 0, 0, 4, 4, 0.25 };
		object.cost = UpgradeCost(20, 10);
	}
	else if (type == "Seaweed") {
		object.description = "50% sea.\n50% weed.";
		object.upgrades = { "Kelp", "Seagrass", "Coral" };
	}
	else if (type == "Kelp") {
		object.description = "It's just some\nwavy Kelp.";
		object.stats = { 0, 0, 0, 0, 5, 1 };
		object.cost = UpgradeCost(10, 6);
		object.upgrades = { "Red Algae" };
	}
	else if (type == "Red Algae") {
		object.description = "Defender of\nthe reef.";
		object.stats = { 0, 0, 0, 0, 8, 2 };
		object.cost = UpgradeCost(20, 10);
	}
	else if (type == "Seagrass") {
		object.description = "Easy to grow.\nGathers light.";
		object.stats = { 2, 0, 0, 1, 0, 0 };
		object.cost = UpgradeCost(2, 2);
		object.upgrades = { "Gulfweed" };
	}
	else if (type == "Gulfweed") {
		object.description = "Gathers even\nmore light.";
		object.stats = { 4, 0, 0, 3, 0, 0 };
		object.cost = UpgradeCost(10, 4);
	}
	else if (type == "Coral") {
		object.description = "Beautiful! Stores\na lot of stuff.";
		object.stats = { 6, 6, 6 };
		object.cost = UpgradeCost(6, 6);
		object.upgrades = { "Sea Sponge", "Sea Anemone" };
	}
	else if (type == "Sea Sponge") {
		object.description = "Filters saltwater\ninto freshwater";
		object.stats = { 0, 6, 0, 0, 0, 0, 1, 1, 1 };
		object.cost = UpgradeCost(15, 6);
	}
	else if (type == "Sea Anemone") {
		object.description = "Very dangerous,\nbut no reach.";
		object.stats = { 0, 0, 0, 0, 4, 4 };
		object.cost = UpgradeCost(15, 10);
	}
	else if (type == "Mother Tree") {
		object.description = "The grove's heart.\nKeep it alive.";
		object.stats = { 20, 10, 20, 3, 5, 0.5 };
		object.upgrades = { "Grand Mother" };
	}
	else if (type == "Grand Mother") {
		object.description = "An Old Mom.\nHealthy as ever.";
		object.stats = { 50, 50, 50, 6, 10, 1 };
		object.cost = UpgradeCost(30, 30);
	}
	return object;
}

std::vector<std::string> getTreeUpgradeOptions(std::string type) {
	return getTreeMetaObject(type).upgrades;
}

UpgradeCost getTreeUpgradeCost(std::string type) {
	return getTreeMetaObject(type).cost;
}

std::string getTreeDescription(std::string type) {
	return getTreeMetaObject(type).description;
}

TreeStats getTreeStats(std::string type) {
	return getTreeMetaObject(type).stats;
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

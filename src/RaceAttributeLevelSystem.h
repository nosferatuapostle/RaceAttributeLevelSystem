#pragma once
#include <unordered_set>

class RaceAttributeLevelSystem
{
public:
	struct RaceAttributes
	static void UpdateAttributes(RE::PlayerCharacter* player, uint16_t currentLevel);

private:
	static const std::unordered_map<RE::FormID, RaceAttributes> raceAttributesMap;
}

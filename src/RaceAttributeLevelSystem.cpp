#include "RaceAttributeLevelSystem.h"

struct RaceAttributeLevelSystem::RaceAttributes
{
	float baseHealth = 50.0f;
	float baseMagicka = 50.0f;
	float baseStamina = 50.0f;
	float healthIncrease = 0.0f;
	float magickaIncrease = 0.0f;
	float staminaIncrease = 0.0f;
}

void RaceAttributeLevelSystem::UpdateAttributes(RE::PlayerCharacter* player, uint16_t currentLevel)
{
	RE::TESRace* race = RE::PlayerCharacter::GetSingleton()->GetRace();
	RaceAttributeLevelSystem::RaceAttributes attributes;
	auto it = RaceAttributeLevelSystem::raceAttributesMap.find(race->GetFormID());
	if (it != RaceAttributeLevelSystem::raceAttributesMap.end()) {
		attributes = it->second;
	}
	
	float health = attributes.baseHealth + (currentLevel - 1) * attributes.healthIncrease;
	float magicka = attributes.baseMagicka + (currentLevel - 1) * attributes.magickaIncrease;
	float stamina = attributes.baseStamina + (currentLevel - 1) * attributes.staminaIncrease;
	
	float healthDifference = newHealth - player->GetActorValue(RE::ActorValue::kHealth);
    float magickaDifference = newMagicka - player->GetActorValue(RE::ActorValue::kMagicka);
    float staminaDifference = newStamina - player->GetActorValue(RE::ActorValue::kStamina);
	
	a->ModActorValue(RE::ActorValue::kHealth, healthDifference);
	a->ModActorValue(RE::ActorValue::kMagicka, magickaDifference);
	a->ModActorValue(RE::ActorValue::kStamina, staminaDifference);
}

const std::unordered_map<RE::FormID, RaceAttributeLevelSystem::RaceAttributes> RaceAttributeLevelSystem::raceAttributesMap = {
		{ 79680, { 115.0f, 75.0f, 110.0f, 4.0f, 2.0f, 4.0f } },    // Argonian
		{ 79681, { 90.0f, 115.0f, 95.0f, 2.0f, 5.0f, 3.0f } },     // Breton
		{ 79682, { 105.0f, 105.0f, 105.0f, 3.0f, 3.0f, 3.0f } },   // DarkElf
		{ 79683, { 85.0f, 125.0f, 90.0f, 2.0f, 7.0f, 2.0f } },     // HighElf
		{ 79684, { 110.0f, 80.0f, 110.0f, 4.0f, 2.0f, 4.0f } },    // Imperial
		{ 79685, { 100.0f, 75.0f, 125.0f, 3.0f, 2.0f, 6.0f } },    // Khajiit
		{ 79686, { 120.0f, 70.0f, 110.0f, 5.0f, 1.0f, 4.0f } },    // Nord
		{ 79687, { 125.0f, 60.0f, 115.0f, 6.0f, 1.0f, 4.0f } },    // Orc
		{ 79688, { 115.0f, 65.0f, 120.0f, 4.0f, 1.0f, 5.0f } },    // Redguard
		{ 79689, { 95.0f, 90.0f, 115.0f, 2.0f, 3.0f, 5.0f } },     // WoodElf
		{ 559162, { 115.0f, 75.0f, 110.0f, 5.0f, 3.0f, 5.0f } },   // ArgonianRaceVampire
		{ 559164, { 90.0f, 115.0f, 95.0f, 3.0f, 6.0f, 4.0f } },    // BretonRaceVampire
		{ 559165, { 105.0f, 105.0f, 105.0f, 4.0f, 4.0f, 4.0f } },  // DarkElfRaceVampire
		{ 559168, { 85.0f, 125.0f, 90.0f, 3.0f, 8.0f, 3.0f } },    // HighElfRaceVampire
		{ 559172, { 110.0f, 80.0f, 110.0f, 5.0f, 3.0f, 5.0f } },   // ImperialRaceVampire
		{ 559173, { 100.0f, 75.0f, 125.0f, 4.0f, 3.0f, 7.0f } },   // KhajiitRaceVampire
		{ 558996, { 120.0f, 70.0f, 110.0f, 6.0f, 2.0f, 5.0f } },   // NordRaceVampire
		{ 688825, { 125.0f, 60.0f, 115.0f, 7.0f, 2.0f, 5.0f } },   // OrcRaceVampire
		{ 559174, { 115.0f, 65.0f, 120.0f, 5.0f, 2.0f, 6.0f } },   // RedguardRaceVampire
		{ 559236, { 95.0f, 90.0f, 115.0f, 3.0f, 5.0f, 6.0f } }     // WoodElfRaceVampire
};
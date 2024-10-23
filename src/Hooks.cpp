#include "Hooks.h"
#include "Events.h"
#include "RaceAttributeLevelSystem.h"

class LevelUpMenuHook
{
	static void LevelUpMenu()
	{
		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		player->skills->AdvanceLevel(false);
		RaceAttributeLevelSystem::UpdateAttributes(player, player->GetLevel());
	}

public:
	static void disableLevelUpMenu() { SKSE::GetTrampoline().write_call<5>(REL::ID(51638).address() + 0xf8e, &LevelUpMenu); }
};

void Hooks::Install()
{
	LevelUpMenuHook::disableLevelUpMenu();
}

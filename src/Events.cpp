#include "Events.h"
#include "RaceAttributeLevelSystem.h"
//#include <chrono>
//#include <thread>

class TESSwitchRaceCompleteEventHandler : public RE::BSTEventSink<RE::TESSwitchRaceCompleteEvent>
{
	using EventResult = RE::BSEventNotifyControl;

	virtual EventResult ProcessEvent(const RE::TESSwitchRaceCompleteEvent* a_event,
		RE::BSTEventSource<RE::TESSwitchRaceCompleteEvent>*)
	{
		RE::PlayerCharacter* player = a_event->subject->As<RE::PlayerCharacter>()->GetSingleton();
		if (a_event && a_event->subject) {
			RE::Actor* actor = a_event->subject->As<RE::Actor>();
			if (actor && actor->IsPlayerRef()) {
				RaceAttributeLevelSystem::UpdateAttributes(player, player->GetLevel());
			}
		}

		return EventResult::kContinue;
	}

public:
	static TESSwitchRaceCompleteEventHandler* GetSingleton()
	{
		static TESSwitchRaceCompleteEventHandler handler;
		return &handler;
	}

	static void RegisterTESSwitchRaceCompleteEventHandler()
	{
		auto scriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
		if (scriptEventSource) {
			scriptEventSource->AddEventSink(TESSwitchRaceCompleteEventHandler::GetSingleton());
		}
	}
};

class LoadGameEventHandler : public RE::BSTEventSink<RE::TESLoadGameEvent>
{
public:
	using EventResult = RE::BSEventNotifyControl;

	virtual EventResult ProcessEvent(const RE::TESLoadGameEvent*, RE::BSTEventSource<RE::TESLoadGameEvent>*)
	{
		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		RaceAttributeLevelSystem::UpdateAttributes(player, player->GetLevel());
		return EventResult::kContinue;
	}

	static LoadGameEventHandler* GetSingleton()
	{
		static LoadGameEventHandler handler;
		return &handler;
	}

	static void RegisterLoadGameEventHandler()
	{
		auto scriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
		if (scriptEventSource) {
			scriptEventSource->AddEventSink(LoadGameEventHandler::GetSingleton());
		}
	}
};

class TESDeathEventHandler : public RE::BSTEventSink<RE::TESDeathEvent>
{
	using EventResult = RE::BSEventNotifyControl;

	virtual EventResult ProcessEvent(const RE::TESDeathEvent* a_event, RE::BSTEventSource<RE::TESDeathEvent>*)
	{
		if (!a_event || !a_event->actorDying) {
			return EventResult::kContinue;
		}

		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();

		float exp = 0.0f;

		if (a_event->actorKiller && a_event->actorKiller.get()->IsPlayerRef() && a_event->actorDying) {
			RE::Actor* dyingActor = a_event->actorDying.get()->As<RE::Actor>();
			RE::Actor* killerActor = a_event->actorKiller.get()->As<RE::Actor>();

			if (dyingActor && killerActor && (dyingActor != killerActor)) {
				if (dyingActor->IsDead()) {
					exp = (float)(((float)dyingActor->GetLevel() / (float)player->GetLevel()) * (float)dyingActor->GetLevel() + 1);
					player->skills->data->xp += exp;
					std::string message = fmt::format("{} {} lvl, +{} xp", dyingActor->GetName(), dyingActor->GetLevel(), (int)exp);
					RE::DebugNotification(message.c_str());
				}
			}
		}

		return EventResult::kContinue;
	}

public:
	static TESDeathEventHandler* GetSingleton()
	{
		static TESDeathEventHandler handler;
		return &handler;
	}

	static void RegisterTESDeathEventHandler()
	{
		auto scriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
		if (scriptEventSource) {
			scriptEventSource->AddEventSink(TESDeathEventHandler::GetSingleton());
		}
	}
};

void Events::Register()
{
	TESSwitchRaceCompleteEventHandler::RegisterTESSwitchRaceCompleteEventHandler();
	LoadGameEventHandler::RegisterLoadGameEventHandler();
	TESDeathEventHandler::RegisterTESDeathEventHandler();
}



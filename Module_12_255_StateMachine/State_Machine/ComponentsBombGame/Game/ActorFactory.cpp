#include "ActorFactory.h"

#include <concepts>
#include <filesystem>
#include <fstream>

#include "World.h"
#include "Appearances.h"
#include "GameTags.h"

#include "../Engine/ActorTags.h"
#include "EnemyComponents.h"
#include "PlayerComponents.h"
#include "TileComponents.h"
#include "HealthTracker.h"


namespace ActorFactory {
	using enum TileAppearance;

	Actor* CreateEmptyTile(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kEmptyTile, pWorld, Pos);
		newActor->GetComponent<ActorTags>()->GiveTag(GameTag::kEmpty);
		return newActor;
	}

	Actor* CreateBombTile(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kBombTile, pWorld, Pos);

		return newActor;
	}

	Actor* CreateMimicTile(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kMimicTile, pWorld, Pos);

		return newActor;
	}

	Actor* CreateExitTile(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kExitTile, pWorld, Pos);

		return newActor;
	}

	Actor* CreateTreasureTile(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kTreasureTile, pWorld, Pos);
		newActor->GetComponent<ActorTags>()->GiveTag(GameTag::kTreasure);
		return newActor;
	}

	///////////////////////////////////////////////////////////////
	// TeleportCollide Component Requires Init of linked position
	///////////////////////////////////////////////////////////////
	Actor* CreateTeleporterTile(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kTeleporterTile, pWorld, Pos);
		newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_YEL);

		return newActor;
	}

	Actor* CreateDirectEnemy(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kDirectEnemy, pWorld, Pos);
		newActor->GetComponent<HealthTracker>()->SetHealth(1);
		newActor->GetComponent<EnemyLogic>()->Init(EnemyLogic::EnemyType::kDirect);
		newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_RED);

		return newActor;
	}

	Actor* CreateScaredEnemy(World* pWorld, Actor::Position_t Pos)
	{
		Actor* newActor = CreateActor(ActorTypes::kScaredEnemy, pWorld, Pos);
		newActor->GetComponent<HealthTracker>()->SetHealth(1);
		newActor->GetComponent<EnemyLogic>()->Init(EnemyLogic::EnemyType::kScared);
		newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_RGB(255, 0, 0));

		return newActor;
	}

	Actor* Createplayer(World* pWorld, Actor::Position_t Pos, int startingHealth)
	{
		Actor* newActor = CreateActor(ActorTypes::kPlayer, pWorld, Pos);
		newActor->GetComponent<HealthTracker>()->SetHealth(startingHealth);
		newActor->GetComponent<ActorTags>()->GiveTag(GameTag::kPlayer);
		newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_RGB(0, 255, 255));

		return newActor;
	}


	///////////////////////////////////////////////////////////////
	// Fills the Actor map with information from the file
	// "Game/ActorPrototypes.txt"
	///////////////////////////////////////////////////////////////
	static void FillMap(ActorMap* pActorMap)
	{
		static std::string identifiers[]
		{
			"EmptyTile",
			"BombTile",
			"MimicTile",
			"ExitTile",
			"TreasureTile",
			"TeleporterTile",
			"DirectEnemy",
			"ScaredEnemy",
			"Player"
		};

		std::fstream file;
		file.open("Game/ActorPrototypes.txt");
		assert(file.is_open());

		std::string line;
		while (std::getline(file, line))
		{
			if (line.size() == 0)
				continue;

			if (line.back() != ':')
				continue;

			line.erase((line.end() - 1));
			for (size_t i = 0; i < std::size(identifiers); ++i)
			{
				if (identifiers[i] != line)
					continue;

				ActorInfo& actorInfo = (*pActorMap)[(ActorTypes)i];

				while (file.peek() == '\t')
				{
					file.ignore();
					std::getline(file, line);
					size_t appearancePos = line.find("Appearance = ");
					if (appearancePos != std::string::npos)
					{
						actorInfo.m_appearance = line.back();
						continue;
					}
					actorInfo.m_componentIds.emplace_back(StringHash(line.c_str()));
				}

			}
		}

		file.close();
		return;
	}

	///////////////////////////////////////////////////////////////
	// Creates and actor based on the type
	///////////////////////////////////////////////////////////////
	Actor* CreateActor(ActorTypes actorType, World* pWorld, Actor::Position_t Pos)
	{
		assert(actorType != ActorTypes::kCount || "cannot create a kCount actor");
		static bool mapFilled = false;
		static ActorMap ActorMap;

		if (!mapFilled)
		{
			FillMap(&ActorMap);
			mapFilled = true;
		}

		Actor* newActor = new Actor;
		for (uint32_t id : ActorMap.at(actorType).m_componentIds)
		{
			newActor->AddComponent(id);
		}
		auto sprite = ActorMap.at(actorType).m_appearance;
		if (sprite != '\0')
			newActor->GetComponent<BasicRenderer>()->ChangeSprite(sprite);
		newActor->Init(pWorld, Pos);

		return newActor;
	}

}
#pragma once

#if WITH_AUTOMATION_TESTS

#include "GameFramework/WorldSettings.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "EngineUtils.h"

class FSimpleWorldFixture {
public:
	// for now we'll just define methods in the header directly
	// Explicit, We don't ever want temporary worlds instantiated -> create it. and pass a pointer to any users
	explicit FSimpleWorldFixture()
	{
		if (GEngine != nullptr)
		{
			static uint32 WorldCounter = 0;
			const FString WorldName = FString::Printf(TEXT("WorldFixture_%d"), WorldCounter++); // worlds need to have unique names?

			if (UWorld* World = UWorld::CreateWorld(EWorldType::Game, false, *WorldName, GetTransientPackage()))
			{
				FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);
				WorldContext.SetCurrentWorld(World);
				World->InitializeActorsForPlay(FURL());
				if (IsValid(World->GetWorldSettings()))
				{
					World->GetWorldSettings()->NotifyBeginPlay();
					World->GetWorldSettings()->NotifyMatchStarted();
				}

				World->BeginPlay();
				TestWorld = MakeWeakObjectPtr(World);
			}
		}
	}

	UWorld* GetWorld() const { return TestWorld.Get(); }

	~FSimpleWorldFixture()
	{
		// tear down
		UWorld* World = TestWorld.Get();
		if (World != nullptr && GEngine != nullptr)
		{
			//World->BeginTearingDown();
			World->EndPlay(EEndPlayReason::Destroyed); //This necessary (warnings in event log otherwise) -> this also causes 'begin tearing down to run'
			for (auto It = TActorIterator<AActor>(World); It; ++It)
			{
				It->Destroy();
			}
			GEngine->DestroyWorldContext(World);
			World->DestroyWorld(false);
		}
	}

private:
	TWeakObjectPtr<UWorld> TestWorld;
};

#endif
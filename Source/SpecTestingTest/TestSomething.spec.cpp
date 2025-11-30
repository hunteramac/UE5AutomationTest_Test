#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "MyActor.h"

#include "GameFramework/WorldSettings.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "EngineUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlaceholderTest, "TestGroup.TestSubgroup.Placeholder Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlaceholderTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	return true;
}

BEGIN_DEFINE_SPEC(FMyActorSpec, "MyActor",
	EAutomationTestFlags_ApplicationContextMask |
	EAutomationTestFlags::ProductFilter
)

uint32 WorldCounter = 0;
TWeakObjectPtr<UWorld> TestWorld;
TWeakObjectPtr<AMyActor> TestSubject;

END_DEFINE_SPEC(FMyActorSpec)

void FMyActorSpec::Define()
{
	Describe("AMyActor", [this]()
	{
		BeforeEach([this]()
		{
			// setup the world 
			if (GEngine != nullptr)
			{
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

					if (TestNotNull("World", TestWorld->GetWorld()))
					{
						TestSubject = TestWorld->GetWorld()->SpawnActor<AMyActor>();
						TestNotNull("MyActor", TestSubject.Get());
					}
				}
			}
			// spawn in actor to world
		});

		AfterEach([this]()
		{
			// tear down
			UWorld* World = TestWorld.Get();
			if (World != nullptr && GEngine != nullptr)
			{
				World->EndPlay(EEndPlayReason::Destroyed); //is this necessary?
				World->BeginTearingDown();
				for (auto It = TActorIterator<AActor>(World); It; ++It)
				{
					It->Destroy();
				}
				GEngine->DestroyWorldContext(World);
				World->DestroyWorld(false);
			}
		});

		It("Should not have this test fail due to errors in setup or teardown", [this]()
		{
				TestTrue("true", true);
		});

		// this test is going to fail
		It("Should do a thing", [this]()
		{
				TestTrue("doThing()", TestSubject->doAThing());
		});
	});
}

//DEFINE_SPEC(MyCustomSpec, "MyGame.MyCustomSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)
//void MyCustomSpec::Define()
//{
//	Describe("FExampleOne", [this]()
//	{
//		It("should return true", [this]()
//		{
//			TestTrue("athing", true);
//		});
//	});
//}


//DEFINE_SPEC(FMyCustomSpec, "MyGame.MyCustomSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
//void MyCustomSpec::Define()
//{
//	Describe("FExampleFeare", [this]()
//	{
//		It("should return true", [this]()
//		{
//		    TestTrue("athing", true);
//		})
//	});
//}


//BEGIN_DEFINE_SPEC(FExampleSpec, "Example",
//    EAutomationTestFlags::ApplicationContextMask | /*EAutomationTestFlags::*/ProductFilter);
//
//// Variables and functions defined here will end up being member of 
//// the FExampleSpec class and will be accessible in the tests
//
//END_DEFINE_SPEC(FExampleSpec);
//
//void FExampleSpec::Define()
//{
//    Describe("FExampleFeare", [this]() 
//    {
//        It("Should return true", [this]()
//        {
//            TestTrue("AThing", true);
//        });
//    });
//}

#endif
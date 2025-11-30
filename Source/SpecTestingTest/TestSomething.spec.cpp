#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "MyActor.h"

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

TUniquePtr<UWorld> world;
TWeakObjectPtr<AMyActor> subject;

END_DEFINE_SPEC(FMyActorSpec)

void FMyActorSpec::Define()
{
	Describe("AMyActor", [this]()
	{
		BeforeEach([this]()
		{
			// setup the world 
			// spawn in actor to world
		});

		AfterEach([this]()
		{
			// tear down
		});

		It("Should not have this test fail due to errors in setup or teardown", [this]()
		{
			//do nothing
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
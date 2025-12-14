#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "../MyActor.h"
#include "TestFixtures/WorldFixture.h"
#include "../SimManaged.h"

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

TUniquePtr<FSimpleWorldFixture> TestWorld;
TWeakObjectPtr<AMyActor> TestSubject;

END_DEFINE_SPEC(FMyActorSpec)

void FMyActorSpec::Define()
{
	Describe("AMyActor", [this]()
	{
		BeforeEach([this]()
		{
			// setup the world 
			TestWorld = MakeUnique<FSimpleWorldFixture>();

			// add the test subject
			if (TestNotNull("World", TestWorld->GetWorld()))
			{
				TestSubject = TestWorld->GetWorld()->SpawnActor<AMyActor>();
				TestNotNull("MyActor", TestSubject.Get());

				// add sim managed component
				TestSubject.Get()->AddComponentByClass(USimManaged::StaticClass(),false, FTransform::Identity, false);
			}
		});

		AfterEach([this]()
		{
			// tear down
			TestWorld.Reset();
		});

		It("Should not have this test fail due to errors in setup or teardown", [this]()
		{
				TestTrue("true", true);
		});

		It("Should do a thing", [this]()
		{
				TestTrue("doThing()", TestSubject->doAThing());
		});
		
		It("can add 1", [this]() {
			TestEqual("add a thing()", TestSubject->numberOperation(1, 2), 3);
		});

		It("can have Subscribe method called with a provided multicast delegate type", [this]()
		{
			FMulticastDelegate TestDelegateInstance;
			TestSubject->Subscribe(TestDelegateInstance);
			TestTrue("delegate was bound to", TestDelegateInstance.IsBound());
		});

		It("should have a sim managed component attached", [this]()
		{
			auto simManaged = TestSubject->GetComponentByClass<USimManaged>();
			TestNotNull("MyActor", simManaged);
			simManaged->ThisMethodIsExposed();
		});
	});
}

#endif
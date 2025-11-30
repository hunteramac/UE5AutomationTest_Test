//#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
//#include "FPlaceholderTest.generated.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlaceholderTest, "TestGroup.TestSubgroup.Placeholder Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlaceholderTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	return true;
}

//
//DEFINE_SPEC(FMyCustomSpec, "MyGame.MyCustomSpec", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
//void MyCustomSpec::Define()
//{
//	Describe("FExampleFeare", [this]()
//	{
//		it("should return true", [this]()
//		{
//		    testtrue("athing", true);
//		})
//	});
//}

//#endif

//BEGIN_DEFINE_SPEC(FExampleSpec, "Example",
//    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);
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
//        })
//    });
//}

//#endif
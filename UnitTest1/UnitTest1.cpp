#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1_7/Account.h"
#include "../lab1_7/Money.h"
#include "../lab1_7/Account.cpp"
#include "../lab1_7/Money.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Money m1;
            m1.Init(150.75); 

            Money m2;
            m2.Init(50.50); 

            Money result = m1.add(m2);

            double expected = 201.25;
            double actual = result.getTotal();

            Assert::AreEqual(expected, actual, 0.001);
		}
	};
}
